
#include <cerrno>
#include <opencv2/opencv.hpp>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>
}

#include "except.h"


extern "C"
JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_createDetector
        (JNIEnv *env, jclass obj) {
    return jnikit::context<jlong>(env, [](jnikit::Env& env)->jlong {
        apriltag_detector* detector = apriltag_detector_create();
        if (nullptr == detector ) {
            env.throwException<JNIException, jnikit::types::Int>(errno);
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
            env.throwException<JNIException, jnikit::types::Int>(errno);
        }
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_removeFamily
        (JNIEnv *env, jclass obj, jlong ptr, jlong familyPtr) {
    jnikit::context<void>(env, [ptr, familyPtr](jnikit::Env& env)->void {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);
        auto family = reinterpret_cast<apriltag_family*>(familyPtr);

        apriltag_detector_remove_family(detector, family);
        if (errno != 0) {
            env.throwException<JNIException, jnikit::types::Int>(errno);
        }
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_clearFamilies
        (JNIEnv *env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env)->void {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);

        apriltag_detector_clear_families(detector);
        if (errno != 0) {
            env.throwException<JNIException, jnikit::types::Int>(errno);
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
            env.throwException<JNIException, jnikit::types::Int>(errno);
        }

        return reinterpret_cast<jlong>(detections);
    });
}
