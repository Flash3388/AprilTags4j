#include <cerrno>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>
}

#include "except.h"


DEFINE_OBJECT_TYPE(JDetection, "com/flash3388/apriltags4j/Detection")

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

        auto detectionCls = env.getClass<JDetection>();
        using namespace jnikit::types;
        return detectionCls.newInstance<Int, Int, Float, Double, Double>(
                detection->id,
                detection->hamming,
                detection->decision_margin,
                detection->c[0],
                detection->c[1]
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

