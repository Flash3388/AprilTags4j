
#include <cerrno>
#include <jni.h>
#include <jnikit.h>

extern "C" {
#include <apriltag.h>

#include <apriltag/tag36h11.h>
#include <apriltag/tag25h9.h>
#include <apriltag/tag36h10.h>
#include <apriltag/tag16h5.h>
#include <apriltag/tagCircle21h7.h>
#include <apriltag/tagCircle49h12.h>
#include <apriltag/tagCustom48h12.h>
#include <apriltag/tagStandard41h12.h>
#include <apriltag/tagStandard52h13.h>
}


enum class FamilyType {
    TAG36H11 = 0,
    TAG25H9,
    TAG36H10,
    TAG16H5,
    TAGCIRCLE21H7,
    TAGCIRCLE49H12,
    TAGCUSTOM48H12,
    TAGSTANDARD41H12,
    TAGSTANDARD52H13
};

DEFINE_OBJECT_TYPE(JFamilyType, "com/flash3388/apriltags4j/FamilyType")

static FamilyType getFamilyType(jnikit::Env& env, jobject typeObj) {
    using namespace jnikit::types;
    auto getOrdinal = env.getClass<JFamilyType>().method<Int()>("ordinal");
    jint ordinal = getOrdinal.call(typeObj);
    return static_cast<FamilyType>(ordinal);
}


extern "C"
JNIEXPORT jlong JNICALL Java_com_flash3388_apriltags4j_AprilTagsFamilyJNI_create
        (JNIEnv *env, jclass obj, jobject type) {
    return jnikit::context<jlong>(env, [&type](jnikit::Env& env)->jlong {
        auto familyType = getFamilyType(env, type);

        apriltag_family_t* family;
        switch (familyType) {
            case FamilyType::TAG36H11:
                family = tag36h11_create();
                break;
            case FamilyType::TAG25H9:
                family = tag25h9_create();
                break;
            case FamilyType::TAG36H10:
                family = tag36h10_create();
                break;
            case FamilyType::TAG16H5:
                family = tag16h5_create();
                break;
            case FamilyType::TAGCIRCLE21H7:
                family = tagCircle21h7_create();
                break;
            case FamilyType::TAGCIRCLE49H12:
                family = tagCircle49h12_create();
                break;
            case FamilyType::TAGCUSTOM48H12:
                family = tagCustom48h12_create();
                break;
            case FamilyType::TAGSTANDARD41H12:
                family = tagStandard41h12_create();
                break;
            case FamilyType::TAGSTANDARD52H13:
                family = tagStandard52h13_create();
                break;
            default:
                break;
        }

        if (nullptr == family || errno != 0) {
            // TODO: HANDLE ERROR
        }

        return reinterpret_cast<jlong>(family);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_com_flash3388_apriltags4j_AprilTagsFamilyJNI_destroy
        (JNIEnv *env, jclass obj, jobject type, jlong ptr) {
    jnikit::context<void>(env, [&type, ptr](jnikit::Env& env)->void {
        auto family = reinterpret_cast<apriltag_family_t*>(ptr);
        auto familyType = getFamilyType(env, type);

        switch (familyType) {
            case FamilyType::TAG36H11:
                tag36h11_destroy(family);
                break;
            case FamilyType::TAG25H9:
                tag25h9_destroy(family);
                break;
            case FamilyType::TAG36H10:
                tag36h10_destroy(family);
                break;
            case FamilyType::TAG16H5:
                tag16h5_destroy(family);
                break;
            case FamilyType::TAGCIRCLE21H7:
                tagCircle21h7_destroy(family);
                break;
            case FamilyType::TAGCIRCLE49H12:
                tagCircle49h12_destroy(family);
                break;
            case FamilyType::TAGCUSTOM48H12:
                tagCustom48h12_destroy(family);
                break;
            case FamilyType::TAGSTANDARD41H12:
                tagStandard41h12_destroy(family);
                break;
            case FamilyType::TAGSTANDARD52H13:
                tagStandard52h13_destroy(family);
                break;
            default:
                break;
        }
    });
}


