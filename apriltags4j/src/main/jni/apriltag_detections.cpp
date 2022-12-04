#include <cerrno>
#include <opencv2/opencv.hpp>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>
#include <apriltag_pose.h>
}

#include "except.h"


DEFINE_OBJECT_TYPE(JDetection, "com/flash3388/apriltags4j/Detection")
DEFINE_OBJECT_TYPE(JDetectionInfo, "com/flash3388/apriltags4j/DetectionInfo")
DEFINE_OBJECT_TYPE(JTagPose, "com/flash3388/apriltags4j/TagPose")
DEFINE_OBJECT_TYPE(JMat, "org/opencv/core/Mat")


static jobject nativeMatToJava(jnikit::Env& env, matd_t* mat) {
    using namespace jnikit::types;
    static_assert(sizeof(double) == sizeof(jdouble));

    auto cvMat = new cv::Mat(mat->nrows, mat->ncols, CV_64F, mat->data);
    return env.getClass<JMat>().newInstance<Long>(reinterpret_cast<jlong>(cvMat));
}

extern "C"
JNIEXPORT jint JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectionsJNI_size
        (JNIEnv* env, jclass obj, jlong ptr) {
    return jnikit::context<jint>(env, [ptr](jnikit::Env& env) -> jint {
        auto detections = reinterpret_cast<zarray*>(ptr);
        auto size = zarray_size(detections);
        return static_cast<jint>(size);
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectionsJNI_get
        (JNIEnv* env, jclass obj, jlong ptr, jint index) {
    return jnikit::context<jobject>(env, [ptr, index](jnikit::Env& env) -> jobject {
        auto detections = reinterpret_cast<zarray*>(ptr);
        auto size = zarray_size(detections);
        if (index < 0 || index > size) {
            env.throwException<JNIException, jnikit::types::Int>(errno);
        }

        apriltag_detection_t* detection;
        zarray_get(detections, static_cast<int>(index), &detection);

        using namespace jnikit::types;

        auto corners = env.newObjectArray<DoubleArray>(4);
        for (int i = 0; i < corners.length(); i++) {
            auto corner = env.newArray<Double>(2);
            corner.fill(detection->p[i], 2);
            corners.setElement(i, corner.array());
        }

        auto detectionCls = env.getClass<JDetection>();
        return detectionCls.newInstance<Long, Int, Int, Float, Double, Double, ObjectArray<DoubleArray>, Long>(
                reinterpret_cast<jlong>(detection),
                detection->id,
                detection->hamming,
                detection->decision_margin,
                detection->c[0],
                detection->c[1],
                corners.array(),
                reinterpret_cast<jlong>(detection->family)
        );
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectionsJNI_destroy
        (JNIEnv* env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env) -> void {
        auto detections = reinterpret_cast<zarray*>(ptr);
        apriltag_detections_destroy(detections);
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectionsJNI_estimatePose
        (JNIEnv* env, jclass obj, jlong detectionPtr, jobject detectionInfoRaw) {
    return jnikit::context<jobject>(env, [detectionPtr, detectionInfoRaw](jnikit::Env& env) -> jobject {
        auto detection = reinterpret_cast<apriltag_detection_t*>(detectionPtr);
        auto detectionInfo = env.wrap<JDetectionInfo>(detectionInfoRaw);

        using namespace jnikit::types;

        apriltag_detection_info_t info {
            .det = detection,
            .tagsize = detectionInfo.getField<Double>("tagSize"),
            .fx = detectionInfo.getField<Double>("focalLengthX"),
            .fy = detectionInfo.getField<Double>("focalLengthY"),
            .cx = detectionInfo.getField<Double>("focalCenterX"),
            .cy = detectionInfo.getField<Double>("focalCenterY"),
        };

        apriltag_pose_t pose;
        double error = estimate_tag_pose(&info, &pose);

        jobject position = nativeMatToJava(env, pose.t);
        jobject orientation = nativeMatToJava(env, pose.R);

        using namespace jnikit::types;
        return env.getClass<JTagPose>().newInstance<JMat, JMat, Double>(orientation, position, error);
    });
}
