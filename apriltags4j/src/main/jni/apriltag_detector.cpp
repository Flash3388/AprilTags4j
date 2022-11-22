
#include <cerrno>
#include <opencv2/opencv.hpp>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>
}

#include "except.h"


DEFINE_OBJECT_TYPE(JDetectorConfiguration, "com/flash3388/apriltags4j/DetectorConfiguration")
DEFINE_OBJECT_TYPE(JQuadThreshParams, "com/flash3388/apriltags4j/DetectorConfiguration$QuadThreshParams")

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
JNIEXPORT jobject JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_getConfiguration
        (JNIEnv *env, jclass obj, jlong ptr) {
    return jnikit::context<jobject>(env, [ptr](jnikit::Env& env)->jobject {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);

        using namespace jnikit::types;

        auto config = env.wrap<JDetectorConfiguration>(
                env.getClass<JDetectorConfiguration>().newInstance<>());
        config.setField<Int>("nthreads", detector->nthreads);
        config.setField<Float>("quadDecimate", detector->quad_decimate);
        config.setField<Float>("quadSigma", detector->quad_sigma);
        config.setField<Boolean>("refineEdges", detector->refine_edges);
        config.setField<Double>("decodeSharpening", detector->decode_sharpening);
        config.setField<Boolean>("debug", detector->debug);

        auto quadThreshParams = env.wrap<JQuadThreshParams>(
                env.getClass<JQuadThreshParams>().newInstance<>());
        quadThreshParams.setField<Int>("minClusterPixels", detector->qtp.min_cluster_pixels);
        quadThreshParams.setField<Int>("maxNmaxima", detector->qtp.max_nmaxima);
        quadThreshParams.setField<Float>("criticalRad", detector->qtp.critical_rad);
        quadThreshParams.setField<Float>("cosCriticalRad", detector->qtp.cos_critical_rad);
        quadThreshParams.setField<Float>("maxLineFitMse", detector->qtp.max_line_fit_mse);
        quadThreshParams.setField<Int>("minWhiteBlackDiff", detector->qtp.min_white_black_diff);
        quadThreshParams.setField<Int>("deglitch", detector->qtp.deglitch);

        config.setField<JQuadThreshParams>("quadThreshParams", quadThreshParams.object());

        return config.object();
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsDetectorJNI_setConfiguration
        (JNIEnv *env, jclass obj, jlong ptr, jobject configRaw) {
    jnikit::context<void>(env, [ptr, configRaw](jnikit::Env& env)->void {
        auto detector = reinterpret_cast<apriltag_detector*>(ptr);

        using namespace jnikit::types;

        auto config = env.wrap<JDetectorConfiguration>(configRaw);
        detector->nthreads = config.getField<Int>("nthreads");
        detector->quad_decimate = config.getField<Float>("quadDecimate");
        detector->quad_sigma = config.getField<Float>("quadSigma");
        detector->refine_edges = config.getField<Boolean>("refineEdges");
        detector->decode_sharpening = config.getField<Double>("decodeSharpening");
        detector->debug = config.getField<Boolean>("debug");

        auto quadThreshParamsRaw = config.getField<JQuadThreshParams>("quadThreshParams");
        if (nullptr != quadThreshParamsRaw) {
            auto quadThreshParams = env.wrap<JQuadThreshParams>(quadThreshParamsRaw);
            detector->qtp.min_cluster_pixels = quadThreshParams.getField<Int>("minClusterPixels");
            detector->qtp.max_nmaxima = quadThreshParams.getField<Int>("maxNmaxima");
            detector->qtp.critical_rad = quadThreshParams.getField<Float>("criticalRad");
            detector->qtp.cos_critical_rad = quadThreshParams.getField<Float>("cosCriticalRad");
            detector->qtp.max_line_fit_mse = quadThreshParams.getField<Float>("maxLineFitMse");
            detector->qtp.min_white_black_diff = quadThreshParams.getField<Int>("minWhiteBlackDiff");
            detector->qtp.deglitch = quadThreshParams.getField<Int>("deglitch");
        }
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
        if (nullptr == detections) {
            env.throwException<JNIException, jnikit::types::Int>(errno);
        }

        return reinterpret_cast<jlong>(detections);
    });
}
