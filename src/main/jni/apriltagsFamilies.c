#include <apriltag/tag36h11.h>
#include <apriltag/tag25h9.h>
#include <apriltag/tag36h10.h>
#include <apriltag/tag16h5.h>
#include <apriltag/tagCircle21h7.h>
#include <apriltag/tagCircle49h12.h>
#include <apriltag/tagCustom48h12.h>
#include <apriltag/tagStandard41h12.h>
#include <apriltag/tagStandard52h13.h>
#include <jni.h>

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag36h11Create
        (JNIEnv *env, jclass obj){
   return tag36h11_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag36h11Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tag36h11_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag25h9Create
        (JNIEnv *env, jclass obj){
   return tag25h9_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag25h9Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tag25h9_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag36h10Create
        (JNIEnv *env, jclass obj){
   return tag36h10_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag36h10Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tag36h10_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag16h5Create
        (JNIEnv *env, jclass obj){
   return tag16h5_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tag16h5Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tag16h5_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCircle21h7Create
        (JNIEnv *env, jclass obj){
   return tagCircle21h7_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCircle21h7Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tagCircle21h7_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCircle49h12Create
        (JNIEnv *env, jclass obj){
   return tagCircle49h12_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCircle49h12Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tagCircle49h12_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCustom48h12Create
        (JNIEnv *env, jclass obj){
   return tagCustom48h12_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagCustom48h12Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tagCustom48h12_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagStandard41h12Create
        (JNIEnv *env, jclass obj){
   return tagStandard41h12_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagStandard41h12Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tagStandard41h12_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}

JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagStandard52h13Create
        (JNIEnv *env, jclass obj){
   return tagStandard52h13_create();
}

JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagFamilies_tagStandard52h13Destroy
        (JNIEnv *env, jclass obj, jlong apriltagFamily_t_ptr){
   tagStandard52h13_destroy((apriltag_family_t*)apriltagFamily_t_ptr);
}