#include "configurematerialdialog.h"
#include "ui_configurematerialdialog.h"

ConfigureMaterialDialog::ConfigureMaterialDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfigureMaterialDialog)
{
    m_ui->setupUi(this);
    //
    //Connect the signals
    //
    //Ambient
    connect(m_ui->ambientRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientValuesChanged(double)));
    connect(m_ui->ambientGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientValuesChanged(double)));
    connect(m_ui->ambientBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientValuesChanged(double)));
    connect(m_ui->ambientAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ambientValuesChanged(double)));
    //diffuse
    connect(m_ui->diffuseRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(diffuseValuesChanged(double)));
    connect(m_ui->diffuseGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(diffuseValuesChanged(double)));
    connect(m_ui->diffuseBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(diffuseValuesChanged(double)));
    connect(m_ui->diffuseAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(diffuseValuesChanged(double)));
    //Specular
    connect(m_ui->specularRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(specularValuesChanged(double)));
    connect(m_ui->specularGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(specularValuesChanged(double)));
    connect(m_ui->specularBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(specularValuesChanged(double)));
    connect(m_ui->specularAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(specularValuesChanged(double)));
    //Emission
    connect(m_ui->emissionRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(emissionValuesChanged(double)));
    connect(m_ui->emissionGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(emissionValuesChanged(double)));
    connect(m_ui->emissionBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(emissionValuesChanged(double)));
    connect(m_ui->emissionAlphaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(emissionValuesChanged(double)));
    //Shininess
    connect(m_ui->shininessSlider, SIGNAL(valueChanged(int)), this, SLOT(shininessValuesChanged(int)));
}

ConfigureMaterialDialog::~ConfigureMaterialDialog()
{
    delete m_ui;
}

//Slots
void ConfigureMaterialDialog::ambientValuesChanged(double)
{
    vec4f newIntensity;
    newIntensity[0] = m_ui->ambientRedSpinBox->value();
    newIntensity[1] = m_ui->ambientGreenSpinBox->value();
    newIntensity[2] = m_ui->ambientBlueSpinBox->value();
    newIntensity[3] = m_ui->ambientAlphaSpinBox->value();

    emit ambientChanged(newIntensity);
}
void ConfigureMaterialDialog::diffuseValuesChanged(double)
{
    vec4f newIntensity;
    newIntensity[0] = m_ui->diffuseRedSpinBox->value();
    newIntensity[1] = m_ui->diffuseGreenSpinBox->value();
    newIntensity[2] = m_ui->diffuseBlueSpinBox->value();
    newIntensity[3] = m_ui->diffuseAlphaSpinBox->value();

    emit diffuseChanged(newIntensity);
}
void ConfigureMaterialDialog::specularValuesChanged(double)
{
    vec4f newIntensity;
    newIntensity[0] = m_ui->specularRedSpinBox->value();
    newIntensity[1] = m_ui->specularGreenSpinBox->value();
    newIntensity[2] = m_ui->specularBlueSpinBox->value();
    newIntensity[3] = m_ui->specularAlphaSpinBox->value();

    emit specularChanged(newIntensity);
}
void ConfigureMaterialDialog::emissionValuesChanged(double)
{
    vec4f newIntensity;
    newIntensity[0] = m_ui->emissionRedSpinBox->value();
    newIntensity[1] = m_ui->emissionGreenSpinBox->value();
    newIntensity[2] = m_ui->emissionBlueSpinBox->value();
    newIntensity[3] = m_ui->emissionAlphaSpinBox->value();

    emit emissionChanged(newIntensity);
}
void ConfigureMaterialDialog::shininessValuesChanged(int value)
{
    emit shininessChanged(m_ui->shininessSlider->value());
}

void ConfigureMaterialDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
