/*
    SPDX-FileCopyrightText: 2022 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include <KCModule>

#include "ui_cubeeffectkcm.h"

class CubeEffectConfig : public KCModule
{
    Q_OBJECT

public:
    explicit CubeEffectConfig(QWidget *parent = nullptr, const QVariantList &args = QVariantList());
    ~CubeEffectConfig() override;

public Q_SLOTS:
    void save() override;
    void defaults() override;

private:
    ::Ui::CubeEffectConfig ui;
};
