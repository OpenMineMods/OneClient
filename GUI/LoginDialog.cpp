#include "LoginDialog.h"

#include "Minecraft/Yggdrasil.h"
#include "Utils.h"

LoginDialog::LoginDialog() {
    _ui.setupUi(this);

    setStyleSheet(Utils::loadStyleSheet("main"));

    connect(_ui.loginbutton, &QPushButton::clicked, this, &LoginDialog::loginClicked);
    exec();
}

void LoginDialog::loginClicked() {
    Yggdrasil::login(_ui.username->text(), _ui.password->text());
    done(1);
}
