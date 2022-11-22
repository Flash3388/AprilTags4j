package project;

import com.castle.code.Natives;
import com.castle.exceptions.CodeLoadException;
import com.castle.exceptions.FindException;
import com.flash3388.apriltags4j.Detection;
import com.flash3388.apriltags4j.Detections;
import com.flash3388.apriltags4j.Detector;
import com.flash3388.apriltags4j.DetectorConfiguration;
import com.flash3388.apriltags4j.Family;
import com.flash3388.apriltags4j.FamilyType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Expected argument path to image");
            System.exit(1);
        }

        loadNatives();

        Mat originalImg = Imgcodecs.imread(args[0]);

        Mat gsImg = new Mat();
        Imgproc.cvtColor(originalImg, gsImg, Imgproc.COLOR_BGR2GRAY);

        try (Family family = new Family(FamilyType.TAGCIRCLE21H7); Detector detector = new Detector();) {
            detector.addFamily(family);

            DetectorConfiguration config = detector.getConfiguration();
            System.out.printf("nthread=%d, quadDecimate=%.3f, quadSigma=%.3f\n",
                    config.nthreads, config.quadDecimate, config.quadSigma);

            try (Detections detections = detector.detect(gsImg)) {
                while (detections.hasNext()) {
                    Detection detection = detections.next();
                    Imgproc.putText(
                            originalImg,
                            String.valueOf(detection.id),
                            new Point(detection.centerX, detection.centerY),
                            Imgproc.FONT_HERSHEY_SCRIPT_SIMPLEX,
                            1.0,
                            new Scalar(0xff, 0x99, 0),
                            2
                    );
                }
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        JFrame frame = createWindow();
        JLabel lbl = createImageHolder(frame);
        frame.setVisible(true);
        showImage(lbl, originalImg);
    }

    private static void loadNatives() {
        try {
            Natives.newLoader()
                    .load("opencv_java\\d+", "apriltags_jni");
        } catch (FindException | CodeLoadException | IOException e) {
            throw new Error(e);
        }
    }

    private static void showImage(JLabel lbl, Mat img) {
        SwingUtilities.invokeLater(()-> {
            java.awt.Image awtImage = matToAwtImage(img);
            lbl.setIcon(new ImageIcon(awtImage));
        });
    }

    private static JFrame createWindow() {
        JFrame frame = new JFrame();
        frame.setLayout(new FlowLayout());
        frame.setSize(500, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        return frame;
    }

    private static JLabel createImageHolder(JFrame frame) {
        JLabel lbl = new JLabel();
        lbl.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
        lbl.setSize(200, 200);
        lbl.setVisible(true);

        frame.add(lbl);

        return lbl;
    }

    private static java.awt.Image matToAwtImage(Mat mat) {
        // based on https://riptutorial.com/opencv/example/21963/converting-an-mat-object-to-an-bufferedimage-object
        int type = BufferedImage.TYPE_BYTE_GRAY;
        if (mat.channels() > 1) {
            type = BufferedImage.TYPE_3BYTE_BGR;
        }

        int bufferSize = mat.channels() * mat.cols() * mat.rows();
        byte[] pixels = new byte[bufferSize];
        mat.get(0, 0, pixels); // get all the pixels

        BufferedImage image = new BufferedImage(mat.cols(), mat.rows(), type);
        byte[] targetPixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
        System.arraycopy(pixels, 0, targetPixels, 0, pixels.length);

        return image;
    }
}
