#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox * configGroup = new QGroupBox(tr("Item lifecicle"));

    QLabel * deleteLabel = new QLabel(tr("Delete:"));
    QPushButton * deleteButton = new QPushButton(tr("remove item"));

    QHBoxLayout * deleteLayout = new QHBoxLayout;
    deleteLayout->addWidget(deleteLabel);
    deleteLayout->addWidget(deleteButton);

    QVBoxLayout * configLayout = new QVBoxLayout;
    configLayout->addLayout(deleteLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(itemRemoved()));
}

void ConfigurationPage::itemRemoved()
{
    emit deleteItem();
    close();
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
