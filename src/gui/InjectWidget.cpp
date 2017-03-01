#include "InjectWidget.h"
#include "ui_InjectWidget.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QtAlgorithms>

#include "core.h"

InjectWidget::InjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InjectWidget)
{
    ui->setupUi(this);

    connect(ui->processListComboBox, SIGNAL(clicked()), this, SLOT(populateActiveProcesses()));

    loadSettings();
}

InjectWidget::~InjectWidget()
{
    delete ui;
}

void InjectWidget::saveSettings()
{
    QSettings settings;

    settings.setValue("EnableDebugPrivilege", ui->enableDebugPrivilegeCheckBox->isChecked());
    settings.setValue("LastPayloadPath", payloadPath);
}

void InjectWidget::loadSettings()
{
    QSettings settings;

    if (settings.value("EnableDebugPrivilege").toBool())
        ui->enableDebugPrivilegeCheckBox->setChecked(true);

    payloadPath = settings.value("LastPayloadPath").toString();
    const QFileInfo payloadFile = QFileInfo(payloadPath);
    ui->selectedPayloadLineEdit->setText(payloadFile.fileName());
    ui->selectedPayloadLineEdit->setToolTip(payloadFile.absoluteFilePath());
}

void InjectWidget::on_dllBrowseButton_clicked()
{
    payloadPath = QFileDialog::getOpenFileName(this,
                                               tr("Select Payload"),
                                               R"(.\)",
                                               "DLL Files (*.dll)");

    const QFileInfo payloadFile = QFileInfo(payloadPath);
    ui->selectedPayloadLineEdit->setText(payloadFile.fileName());
    ui->selectedPayloadLineEdit->setToolTip(payloadFile.absoluteFilePath());
}

void InjectWidget::on_injectButton_clicked()
{
    if (payloadPath.isEmpty() || ui->processListComboBox->currentIndex() == -1)
        return;

    if (ui->enableDebugPrivilegeCheckBox->isChecked() && !core::EnableDebugPrivilege())
        ui->messageHistoryPlainTextEdit->appendPlainText(tr("EnableDebugPrivilege failed with code %1.")
                                                         .arg(GetLastError()));

    const unsigned int pid = ui->processListComboBox->currentData().toUInt();

    if (core::CreateRemoteThreadUsingLoadLibrary(pid, payloadPath))
        ui->messageHistoryPlainTextEdit->appendPlainText(tr("CreateRemoteThreadUsingLoadLibrary succeeded."));
    else
        ui->messageHistoryPlainTextEdit->appendPlainText(tr("CreateRemoteThreadUsingLoadLibrary failed with code %1.")
                                                         .arg(GetLastError()));
}

void InjectWidget::populateActiveProcesses()
{
    core::GetActiveProcesses(activeProcesses);

    qSort(activeProcesses.begin(), activeProcesses.end(),
        [](const core::ActiveProcess& a, const core::ActiveProcess& b)
            {return a.name.toLower() < b.name.toLower();});

    ui->processListComboBox->clear();

    for (const auto& process : activeProcesses)
    {
        // TODO: setItemData with a UserRole enum?
        ui->processListComboBox->addItem(process.name,
                                         QVariant(static_cast<unsigned int>(process.pid)));
    }
}
