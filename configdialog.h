#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QtWidgets>

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog();
signals:
    void sendItemDeleted();
    void sendItemUpdated(QBrush);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void receiveItemDeletion();
    void receiveItemUpdate(QBrush);

private:
    void createIcons();

    QListWidget * contentsWidget;
    QStackedWidget * pagesWidget;
};

#endif // CONFIGDIALOG_H
