#include "OBSBasicSettings.hpp"

#include <OBSApp.hpp>
#include <utility/platform.hpp>

#include <qt-wrappers.hpp>

void OBSBasicSettings::InitAppearancePage()
{
	ui->appearanceFontScale->setDisplayTicks(true);

	connect(ui->appearanceFontScale, &QSlider::valueChanged, ui->appearanceFontScaleText,
		[this](int value) { ui->appearanceFontScaleText->setText(QString::number(value)); });
	ui->appearanceFontScaleText->setText(QString::number(ui->appearanceFontScale->value()));

	connect(App(), &OBSApp::StyleChanged, this, &OBSBasicSettings::updateAppearanceControls);
	updateAppearanceControls();
}

void OBSBasicSettings::LoadAppearanceSettings()
{
	loading = true;

	int fontScale = config_get_int(App()->GetUserConfig(), "Appearance", "FontScale");
	ui->appearanceFontScale->setValue(fontScale);

	int densityId = config_get_int(App()->GetUserConfig(), "Appearance", "Density");
	QAbstractButton *densityButton = ui->appearanceDensityButtonGroup->button(densityId);
	if (densityButton) {
		densityButton->setChecked(true);
	}
	updateAppearanceControls();

	loading = false;
}

void OBSBasicSettings::SaveAppearanceSettings()
{
	config_t *config = App()->GetUserConfig();

	config_set_int(config, "Appearance", "FontScale", ui->appearanceFontScale->value());

	int densityId = ui->appearanceDensityButtonGroup->checkedId();
	config_set_int(config, "Appearance", "Density", densityId);

	App()->SetTheme(App()->GetTheme()->id);
}

void OBSBasicSettings::updateAppearanceControls()
{
	OBSTheme *theme = App()->GetTheme();
	enableAppearanceFontControls(theme->usesFontScale);
	enableAppearanceDensityControls(theme->usesDensity);
	if (!theme->usesFontScale || !theme->usesDensity) {
		ui->appearanceOptionsWarning->setVisible(true);
	} else {
		ui->appearanceOptionsWarning->setVisible(false);
	}
	style()->polish(ui->appearanceOptionsWarningLabel);
}

void OBSBasicSettings::enableAppearanceFontControls(bool enable)
{
	ui->appearanceFontScale->setEnabled(enable);
	ui->appearanceFontScaleText->setEnabled(enable);
}

void OBSBasicSettings::enableAppearanceDensityControls(bool enable)
{
	const QList<QAbstractButton *> buttons = ui->appearanceDensityButtonGroup->buttons();
	for (QAbstractButton *button : buttons) {
		button->setEnabled(enable);
	}
}
