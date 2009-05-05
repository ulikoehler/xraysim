#include "configurelightdialog.h"
#include "ui_configurelightdialog.h"

ConfigureLightDialog::ConfigureLightDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfigureLightDialog)
{
    m_ui->setupUi(this);
    /**
     * Connect the signals
     */
    //Ambient intensity
    connect(m_ui->ambientRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientIntensityValuesChanged(double)));
    connect(m_ui->ambientGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientIntensityValuesChanged(double)));
    connect(m_ui->ambientBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientIntensityValuesChanged(double)));
    connect(m_ui->ambientAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientIntensityValuesChanged(double)));
    //
    //Light 1
    //
    connect(m_ui->light1GroupBox, SIGNAL(toggled(bool)), this, SLOT(light1ToggledChanged(bool)));
    //Position
    connect(m_ui->light1PositionXSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1PositionValuesChanged(double)));
    connect(m_ui->light1PositionYSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1PositionValuesChanged(double)));
    connect(m_ui->light1PositionZSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1PositionValuesChanged(double)));
    //Direction
    connect(m_ui->light1DirectionXSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DirectionValuesChanged(double)));
    connect(m_ui->light1DirectionYSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DirectionValuesChanged(double)));
    connect(m_ui->light1DirectionZSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DirectionValuesChanged(double)));
    //Ambient
    connect(m_ui->light1AmbientRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1AmbientValuesChanged(double)));
    connect(m_ui->light1AmbientGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1AmbientValuesChanged(double)));
    connect(m_ui->light1AmbientBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1AmbientValuesChanged(double)));
    connect(m_ui->light1AmbientAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1AmbientValuesChanged(double)));
    //Diffuse
    connect(m_ui->light1DiffuseRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DiffuseValuesChanged(double)));
    connect(m_ui->light1DiffuseGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DiffuseValuesChanged(double)));
    connect(m_ui->light1DiffuseBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DiffuseValuesChanged(double)));
    connect(m_ui->light1DiffuseAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1DiffuseValuesChanged(double)));
    //Specular
    connect(m_ui->light1SpecularRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1SpecularValuesChanged(double)));
    connect(m_ui->light1SpecularGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1SpecularValuesChanged(double)));
    connect(m_ui->light1SpecularBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1SpecularValuesChanged(double)));
    connect(m_ui->light1SpecularAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1SpecularValuesChanged(double)));
    //Exponent
    connect(m_ui->light1ExponentSpinBox, SIGNAL(valueChanged(double)), this, SLOT(light1ExponentValueChanged(double)));
}

ConfigureLightDialog::~ConfigureLightDialog()
{
    delete m_ui;
}

void ConfigureLightDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }

    thisRef = this;
}

void ConfigureLightDialog::on_light1Cutoff180CheckBox_toggled(bool checked)
{
    //Disable the cutoff spin box if the 180 degrees button is selected; else enable it
    if(checked)
    {
        m_ui->light1CutoffSpinBox->setEnabled(false);
    }
    else
    {
        m_ui->light1CutoffSpinBox->setEnabled(true);
    }

}

void ConfigureLightDialog::ambientIntensityValuesChanged(double)
{
    vec4d newIntensity;
    newIntensity[0] = m_ui->ambientRedSpinBox->value();
    newIntensity[1] = m_ui->ambientGreenSpinBox->value();
    newIntensity[2] = m_ui->ambientBlueSpinBox->value();
    newIntensity[3] = m_ui->ambientAlphaSpinBox->value();

    emit ambientIntensityChanged(newIntensity);
}

void ConfigureLightDialog::light1ToggledChanged(bool enabled)
{
    emit light1Toggled(enabled);
}


void ConfigureLightDialog::light1PositionValuesChanged(double)
{
    vec3f newPosition;

    newPosition[0] = m_ui->light1PositionXSpinBox->value();
    newPosition[1] = m_ui->light1PositionYSpinBox->value();
    newPosition[2] = m_ui->light1PositionZSpinBox->value();

    emit light1PositionChanged(newPosition);
}

void ConfigureLightDialog::light1DirectionValuesChanged(double)
{
    vec3f newDirection;

    newDirection[0] = m_ui->light1DirectionXSpinBox->value();
    newDirection[1] = m_ui->light1DirectionYSpinBox->value();
    newDirection[2] = m_ui->light1DirectionZSpinBox->value();

    emit light1DirectionChanged(newDirection);
}

void ConfigureLightDialog::light1AmbientValuesChanged(double)
{
    vec4f newAmbient;

    newAmbient[0] = m_ui->light1AmbientRedSpinBox->value();
    newAmbient[1] = m_ui->light1AmbientGreenSpinBox->value();
    newAmbient[2] = m_ui->light1AmbientBlueSpinBox->value();
    newAmbient[3] = m_ui->light1AmbientAlphaSpinBox->value();

    emit light1AmbientChanged(newAmbient);
}


void ConfigureLightDialog::light1DiffuseValuesChanged(double)
{
    vec4f newDiffuse;

    newDiffuse[0] = m_ui->light1DiffuseRedSpinBox->value();
    newDiffuse[1] = m_ui->light1DiffuseGreenSpinBox->value();
    newDiffuse[2] = m_ui->light1DiffuseBlueSpinBox->value();
    newDiffuse[3] = m_ui->light1DiffuseAlphaSpinBox->value();

    emit light1DiffuseChanged(newDiffuse);
}

void ConfigureLightDialog::light1SpecularValuesChanged(double)
{
    vec4f newSpecular;

    newSpecular[0] = m_ui->light1SpecularRedSpinBox->value();
    newSpecular[1] = m_ui->light1SpecularGreenSpinBox->value();
    newSpecular[2] = m_ui->light1SpecularBlueSpinBox->value();
    newSpecular[3] = m_ui->light1SpecularAlphaSpinBox->value();

    emit light1SpecularChanged(newSpecular);
}

void ConfigureLightDialog::light1ExponentValueChanged(double value)
{
    emit light1ExponentValueChanged(value);
}
