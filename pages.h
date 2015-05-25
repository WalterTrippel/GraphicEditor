#ifndef PAGES
#define PAGES

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QDateTimeEdit>
#include <QSpinBox>

class ConfigurationPage : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationPage(QWidget *parent = 0);
signals:
    void deleteItem();
public slots:
    void itemRemoved();
};

class UpdatePage : public QWidget
{
public:
    UpdatePage(QWidget *parent = 0);
};

#endif // PAGES

