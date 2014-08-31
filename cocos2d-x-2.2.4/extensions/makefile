CL=cl /c
LINK=link /dll 
CLOUT=/Fo
LINKOUT=/OUT:
INCLUDE=	/I"../../cocos2d-x-2.2.4/cocos2dx/" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/include"  \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/.." \
			/I"../../cocos2d-x-2.2.4/cocos2dx/platform/win32" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/iconv" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/zlib" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/libpng" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/libjpeg" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/libtiff" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/libwebp" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/pthread" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../platform/third_party/win32/OGLES" \
			/I"../include" \
			/I"../../cocos2d-x-2.2.4/cocos2dx/proj.win32/../kazmath/include" \
			/I"../../cocos2d-x-2.2.4/extensions"
OPTION=/EHsc /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COCOS2DXWIN32_EXPORTS" /D "GL_GLEXT_PROTOTYPES" /D "COCOS2D_DEBUG=1" /D "_CRT_SECURE_NO_WARNINGS" /D "_SCL_SECURE_NO_WARNINGS" /D "_USING_V110_SDK71_" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /GS /analyze- /W3 /wd"4267" /wd"4251" /wd"4244" /Zc:wchar_t /ZI /Gm /Od /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo 
DEBUG=
DIR_SRC=../../cocos2d-x-2.2.4/extensions/
BIN=../../cocos2d-x-2.2.4/bin

CCObjs=		../../cocos2d-x-2.2.4/extensions/AssetsManager/AssetsManager.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBAnimationManager.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBFileLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBKeyframe.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBReader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBSequence.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBSequenceProperty.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCBValue.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCControlButtonLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCControlLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCData.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCLabelBMFontLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCLabelTTFLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCLayerColorLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCLayerGradientLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCLayerLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCMenuItemImageLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCMenuItemLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCNode+CCBRelativePositioning.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCNodeLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCNodeLoaderLibrary.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCParticleSystemQuadLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCScale9SpriteLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCScrollViewLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CCBReader/CCSpriteLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionEaseEx.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionFrame.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionFrameEasing.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionManager.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionNode.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Action/CCActionObject.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/ActionTimeline/CCActionTimeline.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/ActionTimeline/CCActionTimelineCache.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/ActionTimeline/CCFrame.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/ActionTimeline/CCNodeReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/ActionTimeline/CCTimeLine.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/animation/CCArmatureAnimation.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/animation/CCProcessBase.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/animation/CCTween.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/CCArmature.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/CCBone.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/datas/CCDatas.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/display/CCBatchNode.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/display/CCDecorativeDisplay.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/display/CCDisplayFactory.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/display/CCDisplayManager.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/display/CCSkin.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/physics/CCColliderDetector.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCArmatureDataManager.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCArmatureDefine.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCDataReaderHelper.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCTransformHelp.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCTweenFunction.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Armature/utils/CCUtilMath.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Components/CCComAttribute.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Components/CCComAudio.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Components/CCComController.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Components/CCComRender.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Components/CCInputDelegate.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/BaseClasses/UIWidget.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/Layouts/UILayout.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/Layouts/UILayoutDefine.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/Layouts/UILayoutParameter.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/System/CocosGUI.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/System/UIHelper.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/System/UITouchGroup.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIListView.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIPageView.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/ScrollWidget/UIScrollView.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UIButton.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UICheckBox.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UIImageView.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UILabel.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UILabelAtlas.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UILabelBMFont.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UILoadingBar.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UIRichText.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UISlider.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/GUI/UIWidgets/UITextField.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Json/CocoLoader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Json/DictionaryHelper.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/GUIReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/SceneReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/ButtonReader/ButtonReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/CheckBoxReader/CheckBoxReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/ImageViewReader/ImageViewReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/LabelAtlasReader/LabelAtlasReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/LabelBMFontReader/LabelBMFontReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/LabelReader/LabelReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/LayoutReader/LayoutReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/ListViewReader/ListViewReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/LoadingBarReader/LoadingBarReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/PageViewReader/PageViewReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/ScrollViewReader/ScrollViewReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/SliderReader/SliderReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/TextFieldReader/TextFieldReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Reader/WidgetReader/WidgetReader.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Trigger/ObjectFactory.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Trigger/TriggerBase.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Trigger/TriggerMng.obj\
		../../cocos2d-x-2.2.4/extensions/CocoStudio/Trigger/TriggerObj.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControl.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlButton.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlColourPicker.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlHuePicker.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlPotentiometer.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlSlider.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlStepper.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlSwitch.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCControlUtils.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCInvocation.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCControlExtension/CCScale9Sprite.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBox.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplAndroid.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplNone.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplTizen.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplWin.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplWinrt.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCEditBox/CCEditBoxImplWp8.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCScrollView/CCScrollView.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCScrollView/CCSorting.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCScrollView/CCTableView.obj\
		../../cocos2d-x-2.2.4/extensions/GUI/CCScrollView/CCTableViewCell.obj\
		../../cocos2d-x-2.2.4/extensions/LocalStorage/LocalStorage.obj\
		../../cocos2d-x-2.2.4/extensions/LocalStorage/LocalStorageAndroid.obj\
		../../cocos2d-x-2.2.4/extensions/network/HttpClient.obj\
		../../cocos2d-x-2.2.4/extensions/network/WebSocket.obj\
		../../cocos2d-x-2.2.4/extensions/network/WebSocketWinRT.obj\
		../../cocos2d-x-2.2.4/extensions/physics_nodes/CCPhysicsDebugNode.obj\
		../../cocos2d-x-2.2.4/extensions/physics_nodes/CCPhysicsSprite.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Animation.obj\
		../../cocos2d-x-2.2.4/extensions/spine/AnimationState.obj\
		../../cocos2d-x-2.2.4/extensions/spine/AnimationStateData.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Atlas.obj\
		../../cocos2d-x-2.2.4/extensions/spine/AtlasAttachmentLoader.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Attachment.obj\
		../../cocos2d-x-2.2.4/extensions/spine/AttachmentLoader.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Bone.obj\
		../../cocos2d-x-2.2.4/extensions/spine/BoneData.obj\
		../../cocos2d-x-2.2.4/extensions/spine/CCSkeleton.obj\
		../../cocos2d-x-2.2.4/extensions/spine/CCSkeletonAnimation.obj\
		../../cocos2d-x-2.2.4/extensions/spine/extension.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Json.obj\
		../../cocos2d-x-2.2.4/extensions/spine/RegionAttachment.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Skeleton.obj\
		../../cocos2d-x-2.2.4/extensions/spine/SkeletonData.obj\
		../../cocos2d-x-2.2.4/extensions/spine/SkeletonJson.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Skin.obj\
		../../cocos2d-x-2.2.4/extensions/spine/Slot.obj\
		../../cocos2d-x-2.2.4/extensions/spine/SlotData.obj\
		../../cocos2d-x-2.2.4/extensions/spine/spine-cocos2dx.obj
CCOBJ_DIR=extensions/
exts:$(CCObjs)
	$(LINK) $(BIN)/$(CCOBJ_DIR)*.obj $(LIB_PUBLIC) /OUT:$(BIN)/$@.dll
%.obj : %.cpp
	$(CL) $(INCLUDE) $(OPTION) $<  -Fo$(BIN)/$(CCOBJ_DIR) /Fd"./bin/cocos2dx.pdb"
$(CCObjs):