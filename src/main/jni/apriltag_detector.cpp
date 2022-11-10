
#include <cerrno>
#include <opencv2/opencv.hpp>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>
}


DEFINE_OBJECT_TYPE(JDetection, "com/flash3388/apriltags4j/Detection")

extern "C"
JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_createDetector
        (JNIEnv *env, jclass obj) {
    return jnikit::context<jlong>(env, [](jnikit::Env& env)->jlong {
        apriltag_detector* detector = apriltag_detector_create();
        if (nullptr == detector || errno != 0) {
            // TODO: HANDLE ERROR
        }

        return reinterpret_cast<jlong>(detector);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_destroyDetector
        (JNIEnv *env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env)->void {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);
        apriltag_detector_destroy(detector);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_addFamily
        (JNIEnv *env, jclass obj, jlong ptr, jlong familyPtr) {
    jnikit::context<void>(env, [ptr, familyPtr](jnikit::Env& env)->void {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);
        auto family = reinterpret_cast<apriltag_family*>(familyPtr);

        apriltag_detector_add_family(detector, family);
        if (errno != 0) {
            // TODO: HANDLE ERROR
        }
    });
}

extern "C"
JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_detect
        (JNIEnv *env, jclass obj, jlong ptr, jlong matPtr) {
    return jnikit::context<jlong>(env, [ptr, matPtr](jnikit::Env& env)->jlong {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);
        auto mat = reinterpret_cast<cv::Mat*>(matPtr);

        image_u8_t img {
            .width = mat->cols,
            .height = mat->rows,
            .stride = mat->cols,
            .buf = mat->data
        };
        auto detections = apriltag_detector_detect(detector, &img);
        if (nullptr == detections || errno != 0) {
            // TODO: HANDLE ERROR
        }

        return reinterpret_cast<jlong>(detections);
    });
}

extern "C"
JNIEXPORT jint JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_detectionsSize
        (JNIEnv *env, jclass obj, jlong ptr) {
    return jnikit::context<jint>(env, [ptr](jnikit::Env& env)->jint {
        auto detections = reinterpret_cast<zarray*>(ptr);
        auto size = zarray_size(detections);
        return static_cast<jint>(size);
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_detectionsGet
        (JNIEnv *env, jclass obj, jlong ptr, jint index) {
    return jnikit::context<jobject>(env, [ptr, index](jnikit::Env& env)->jobject {
        auto detections = reinterpret_cast<zarray*>(ptr);
        auto size = zarray_size(detections);
        if (index < 0 || index > size) {
            // TODO: HANDLE ERROR
        }

        apriltag_detection_t* detection;
        zarray_get(detections, static_cast<int>(index), &detection);

        auto detectionCls = env.getClass<JDetection>();
        using namespace jnikit::types;
        return detectionCls.newInstance<Int,Int,Float,Double,Double>(
                detection->id,
                detection->hamming,
                detection->decision_margin,
                detection->c[0],
                detection->c[1]
        );
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_detectionsDestroy
        (JNIEnv *env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env)->void {
        auto detections = reinterpret_cast<zarray*>(ptr);
        apriltag_detections_destroy(detections);
    });
}
