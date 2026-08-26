#pragma once

#include <QString>

#include <string_view>

inline constexpr char TWCC_PRODUCT_NAME[] = "TWCC Studio";
inline constexpr char TWCC_WEBSITE_URL[] = "https://webcreativecommunity.org/";

inline bool PreserveUpstreamProductReference(const char *lookupValue)
{
	const std::string_view lookup = lookupValue ? lookupValue : "";
	return lookup == "OBSStudio" || lookup == "OBSClassic" || lookup == "Wine.Text" ||
	       lookup == "EncoderMissing.NVENC.Unsupported.Kepler" || lookup == "About.Contribute" ||
	       lookup == "CrashHandling.Labels.PrivacyNotice" || lookup == "Importer.HelpText" ||
	       lookup == "Basic.MainMenu.Help.Website" ||
	       (lookup.size() >= 8 && lookup.substr(0, 8) == "Updater.");
}

inline bool ShouldApplyTWCCBranding(const char *lookupValue)
{
	if (PreserveUpstreamProductReference(lookupValue)) {
		return false;
	}

	const std::string_view lookup = lookupValue ? lookupValue : "";
	constexpr std::string_view productReferences[] = {
		"About",
		"About.Info",
		"AddUrl.Text",
		"AlreadyRunning.Text",
		"AlreadyRunning.Title",
		"Basic.AutoConfig.VideoPage.CanvasExplanation",
		"Basic.Main.RemigrateSceneCollection.CannotMigrate.FailedVideoReset",
		"Basic.MainMenu.File.Exit",
		"Basic.MainMenu.Help.About",
		"Basic.Settings.Advanced.General.ConfirmOnExit",
		"Basic.Settings.Audio.LowLatencyBufferingWarning.Enabled",
		"Basic.Settings.Audio.MultichannelWarning",
		"Basic.Settings.General.HideOBSWindowsFromCapture",
		"Basic.Settings.General.HideOBSWindowsFromCapture.Message",
		"Basic.Settings.General.HideOBSWindowsFromCapture.Tooltip",
		"ChromeOS.Text",
		"ConfirmBWTest.Text",
		"ConfirmExit.Text",
		"CrashHandling.Dialog.Title",
		"CrashHandling.Labels.Text",
		"Exit",
		"FailedToStartStream.FailedToGetOBSVideoInfo",
		"Importer.AutomaticCollectionText",
		"LoadProfileNeedsRestart",
		"LogUploadDialog.Title",
		"MacPermissions.Description",
		"MacPermissions.Description.OpenDialog",
		"MacPermissions.Item.Accessibility.Details",
		"MacPermissions.Item.InputMonitoring.Details",
		"MacPermissions.Item.Microphone.Details",
		"MacPermissions.Item.ScreenRecording.Details",
		"MissingFiles.AutoSearchText",
		"MissingFiles.HelpText",
		"NeedsRestart",
		"Output.StartFailedGeneric",
		"PluginManager.Restart",
		"PluginsFailedToLoad.Text",
		"Remux.HelpText",
		"Remux.OBSRecording",
		"Remux.SelectRecording",
		"Remux.SourceFile",
		"ResetOSXVSyncOnExit",
		"SafeMode.Restart",
		"SafeMode.RestartNormal",
		"SourceLeak.Text",
		"TwitchAuth.TwoFactorFail.Text",
		"YouTube.Auth.WaitingAuth.Text",
	};

	for (const std::string_view productReference : productReferences) {
		if (lookup == productReference) {
			return true;
		}
	}
	return false;
}

inline QString ApplyTWCCBranding(QString text, const char *lookupValue)
{
	if (!ShouldApplyTWCCBranding(lookupValue)) {
		return text;
	}

	text.replace(QStringLiteral("OBS Studio"), QString::fromUtf8(TWCC_PRODUCT_NAME));
	text.replace(QStringLiteral("OBS"), QStringLiteral("TWCC"));
	if (std::string_view(lookupValue ? lookupValue : "") == "SourceLeak.Text") {
		text.replace(QStringLiteral("Obs "), QStringLiteral("TWCC "));
	}
	return text;
}
