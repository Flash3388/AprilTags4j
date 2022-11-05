#include <apriltag.h>
#include <jni.h>


JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTags_createDetector
        (JNIEnv *env, jclass obj){
   return apriltag_detector_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_destroyDetector
        (JNIEnv *env, jclass obj, jlong detectorPtr){
   apriltag_detector_destroy((apriltag_detector_t*) detectorPtr);
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectorAddFamilyBits
        (JNIEnv *env, jclass obj, jlong detectorPtr, jlong apriltagFamilyPtr, jint bitsCorrected){
   apriltag_detector_add_family_bits((apriltag_detector_t*)detectorPtr, (apriltag_family_t*)apriltagFamilyPtr, (int)bitsCorrected);
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectorAddFamily
        (JNIEnv *env, jclass obj, jlong detectorPtr, jlong apriltagFamilyPtr){
   apriltag_detector_add_family((apriltag_detector_t*)detectorPtr, (apriltag_family_t*)apriltagFamilyPtr);
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectorRemoveFamily
        (JNIEnv *env, jclass obj, jlong detectorPtr, jlong apriltagFamilyPtr){
   apriltag_detector_remove_family((apriltag_detector_t*)detectorPtr, (apriltag_family_t*)apriltagFamilyPtr);
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectorClearFamilies
        (JNIEnv *env, jclass obj, jlong detectorPtr, jlong apriltagFamilyPtr){
   apriltag_detector_clear_families((apriltag_detector_t*)detectorPtr);
}

// return ?
JNIEXPORT jobjectArray JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectorDetect
        (JNIEnv *env, jclass obj, jlong detectorPtr, jint img_width, jint img_height, jint img_stride, jbyteArray img_buf){
            jboolean isCopy;
            jbyte* img_buf_raw = (*env)->GetByteArrayElements(env, img_buf, &isCopy);

            image_u8_t img = {
                .width=img_width, .height=img_height, .stride=img_stride, .buf=(uint8_t*) img_buf_raw
            };
            zarray_t* result = apriltag_detector_detect((apriltag_detector_t*)detectorPtr, &img);

            (*env)->ReleaseByteArrayElements(env, img_buf, img_buf_raw, 0);

            jclass det_cls = (*env)->FindClass(env, "com/flash3388/apriltags4j/AprilTagDetection");
            jmethodID det_cls_ctor = (*env)->GetMethodID(env, det_cls, "<init>", "(JIIFDD)V");

            jobjectArray result_arr = (*env)->NewObjectArray(env, zarray_size(result), det_cls, NULL);
            for (int i = 0; i < zarray_size(result); i++) {
                apriltag_detection_t* det;
                zarray_get(result, i, &det);

                jobject obj = (*env)->NewObject(env, det_cls, det_cls_ctor,
                det->family, det->id, det->hamming, det->decision_margin, det->c[0], det->c[1]);

                (*env)->SetObjectArrayElement(env, result_arr, i, obj);
            }

            return result_arr;
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectionDestroy
        (JNIEnv *env, jclass obj, jlong detection_t_ptr){
   apriltag_detection_destroy((apriltag_detection_t*)detection_t_ptr);
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTags_detectionDestroyZarray_t
        (JNIEnv *env, jclass obj, jlong zarray_t_detection_Ptr){
   apriltag_detection_destroy((zarray_t*)zarray_t_detection_Ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTags_apriltagToImage
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr, jint idx){
   return apriltag_to_image((apriltag_family_t*)apriltagFamily_t_ptr, idx);
}