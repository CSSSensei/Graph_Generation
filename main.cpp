#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include "util/UI.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    UI ui(argc, argv, app);

    StartDialog *dialog = new StartDialog();
    dialog->exec();

    if (dialog->result() == QDialog::Accepted && !dialog->isVisible()) {
        return 0; // тест завершил работу
    }

    ui.run(); // основное окно программы

    return 0;
}
