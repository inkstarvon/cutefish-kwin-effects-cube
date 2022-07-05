/*
    SPDX-FileCopyrightText: 2022 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "cubeeffectkcm.h"
#include "cubeconfig.h"

#include <kwineffects_interface.h>

#include <KActionCollection>
#include <KGlobalAccel>
#include <KLocalizedString>
#include <KPluginFactory>

#include <QAction>
#include <QFileDialog>

K_PLUGIN_CLASS(CubeEffectConfig)

CubeEffectConfig::CubeEffectConfig(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
{
    ui.setupUi(this);
    addConfig(CubeConfig::self(), this);

    auto actionCollection = new KActionCollection(this, QStringLiteral("kwin"));
    actionCollection->setComponentDisplayName(i18n("KWin"));
    actionCollection->setConfigGroup(QStringLiteral("cube"));
    actionCollection->setConfigGlobal(true);

    const QKeySequence defaultToggleShortcut = Qt::META | Qt::Key_C;
    QAction *toggleAction = actionCollection->addAction(QStringLiteral("Cube"));
    toggleAction->setText(i18n("Toggle Cube"));
    toggleAction->setProperty("isConfigurationAction", true);
    KGlobalAccel::self()->setDefaultShortcut(toggleAction, {defaultToggleShortcut});
    KGlobalAccel::self()->setShortcut(toggleAction, {defaultToggleShortcut});

    ui.shortcutsEditor->addCollection(actionCollection);
    connect(ui.shortcutsEditor, &KShortcutsEditor::keyChange, this, &CubeEffectConfig::markAsChanged);

    connect(ui.button_SkyBox, &QPushButton::clicked, this, [this]() {
        auto dialog = new QFileDialog(this);
        dialog->setFileMode(QFileDialog::ExistingFile);
        connect(dialog, &QFileDialog::fileSelected, ui.kcfg_SkyBox, &QLineEdit::setText);
        dialog->open();
    });
}

CubeEffectConfig::~CubeEffectConfig()
{
    // If save() is called, undo() has no effect.
    ui.shortcutsEditor->undo();
}

void CubeEffectConfig::save()
{
    KCModule::save();
    ui.shortcutsEditor->save();

    OrgKdeKwinEffectsInterface interface(QStringLiteral("org.kde.KWin"), QStringLiteral("/Effects"), QDBusConnection::sessionBus());
    interface.reconfigureEffect(QStringLiteral("cube"));
}

void CubeEffectConfig::defaults()
{
    ui.shortcutsEditor->allDefault();
    KCModule::defaults();
}

#include "cubeeffectkcm.moc"
