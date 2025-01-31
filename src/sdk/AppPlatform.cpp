#include "AppPlatform.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

jobject AppPlatform::getMainActivity() {
	return *(jobject*) ((uintptr_t) this + APP_PLATFORM_MAIN_ACTIVITY_OFF);
}

void AppPlatform::setClipboardText(std::string const& str) {
	JNIEnv* env;
	game.jvm->AttachCurrentThread(&env, nullptr);
	{
		jclass context_class = env->FindClass("android/content/Context");
		jclass clipboard_manager_class = env->FindClass("android/content/ClipboardManager");
		jclass clip_data_class = env->FindClass("android/content/ClipData");

		jstring clipboard_service_name = env->NewStringUTF("clipboard");
		jobject clipboard_manager_instance = env->CallObjectMethod(getMainActivity(), env->GetMethodID(context_class, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;"), clipboard_service_name);

		jstring label = env->NewStringUTF("text");
		jstring text = env->NewStringUTF(str.c_str());
		jobject clip_data = env->CallStaticObjectMethod(clip_data_class, env->GetStaticMethodID(clip_data_class, "newPlainText", "(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;"), label, text);

		env->CallVoidMethod(clipboard_manager_instance, env->GetMethodID(clipboard_manager_class, "setPrimaryClip", "(Landroid/content/ClipData;)V"), clip_data);

		env->DeleteLocalRef(clip_data);
		env->DeleteLocalRef(text);
		env->DeleteLocalRef(label);
		env->DeleteLocalRef(clipboard_manager_instance);
		env->DeleteLocalRef(clipboard_service_name);
		env->DeleteLocalRef(clip_data_class);
		env->DeleteLocalRef(clipboard_manager_class);
		env->DeleteLocalRef(context_class);
	}
	game.jvm->DetachCurrentThread();
}

std::string AppPlatform::getClipboardText() {
	std::string result;
	JNIEnv* env;
	game.jvm->AttachCurrentThread(&env, nullptr);
	{
		jclass context_class = env->FindClass("android/content/Context");
		jclass clipboard_manager_class = env->FindClass("android/content/ClipboardManager");
		jclass clip_data_class = env->FindClass("android/content/ClipData");
		jclass item_class = env->FindClass("android/content/ClipData$Item");
		jclass char_sequence_class = env->FindClass("java/lang/CharSequence");

		jstring clipboard_service_name = env->NewStringUTF("clipboard");
		jobject clipboard_manager_instance = env->CallObjectMethod(getMainActivity(), env->GetMethodID(context_class, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;"), clipboard_service_name);
		jobject clip_data = env->CallObjectMethod(clipboard_manager_instance, env->GetMethodID(clipboard_manager_class, "getPrimaryClip", "()Landroid/content/ClipData;"));
		if (clip_data) {
			jobject item = env->CallObjectMethod(clip_data, env->GetMethodID(clip_data_class, "getItemAt", "(I)Landroid/content/ClipData$Item;"), 0);
			if (item) {
				// idk why but getText method returns SpannableString, not CharSequence
				jobject spannable = env->CallObjectMethod(item, env->GetMethodID(item_class, "getText", "()Ljava/lang/CharSequence;"));
				jstring text = (jstring) env->CallObjectMethod(spannable, env->GetMethodID(char_sequence_class, "toString", "()Ljava/lang/String;"));
				result = env->GetStringUTFChars(text, nullptr);
				env->DeleteLocalRef(text);
				env->DeleteLocalRef(spannable);
				env->DeleteLocalRef(item);
			}
			env->DeleteLocalRef(clip_data);
		}
		env->DeleteLocalRef(clipboard_manager_instance);
		env->DeleteLocalRef(clipboard_service_name);
		env->DeleteLocalRef(char_sequence_class);
		env->DeleteLocalRef(item_class);
		env->DeleteLocalRef(clip_data_class);
		env->DeleteLocalRef(clipboard_manager_class);
		env->DeleteLocalRef(context_class);
	}
	game.jvm->DetachCurrentThread();
	return result;
}