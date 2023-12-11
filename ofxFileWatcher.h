#include "ofMain.h"

class ofxFileWatcher {
public:
    ofxFileWatcher() : mFileExists(false), mLastCheck(0.0f) {}

    void setFile(const of::filesystem::path& filePath) {
        mFilePath = ofToDataPath(filePath);
		ofLogNotice("FileWatcher") << "Watching file: " << mFilePath;
        if (!std::filesystem::exists(mFilePath)) {
			ofLogError("FileWatcher") << "File does not exist: " << mFilePath;
            mFileExists = false;
        } else {
            mLastModified = std::filesystem::last_write_time(mFilePath);
            mFileExists = true;
        }
    }

    bool hasFileChanged() {
		if (ofGetElapsedTimef() - mInterval > mLastCheck) {
			mLastCheck = ofGetElapsedTimef();
			ofLogVerbose("FileWatcher") << "Checking for file changes...";
			if (!mFileExists) {
				return false;
			}

			auto currentLastModified = std::filesystem::last_write_time(mFilePath);
			if (currentLastModified != mLastModified) {
				ofLogVerbose("FileWatcher") << "Detected file change.";
				mLastModified = currentLastModified;
				return true;
			}
		}
        return false;
    }

private:
    std::string mFilePath;
    std::filesystem::file_time_type mLastModified;
    bool mFileExists;
	float mLastCheck;
	float mInterval = 3.0f;
};
