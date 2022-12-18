/*
 * The Final Quest - 3D Graphics Engine
 * Copyright (C) 2007  Adam Sawicki
 * http://regedit.gamedev.pl, sawickiap@poczta.onet.pl
 * License: GNU GPL
 */
#pragma once

#include "GameBase.hpp"

class GameRts_pimpl;

class GameRts : public GameBase
{
public:
	GameRts();
	virtual ~GameRts();

	////// Implementacja GameBase
	virtual int CalcFrame();
	virtual void Draw2D() { }
	virtual void OnResolutionChanged();
	virtual void OnMouseMove(const common::VEC2 &Pos);
	virtual void OnMouseButton(const common::VEC2 &Pos, frame::MOUSE_BUTTON Button, frame::MOUSE_ACTION Action);
	virtual void OnMouseWheel(const common::VEC2 &Pos, float Delta);

protected:
	////// Implementacja GameBase
	virtual engine::Scene * GetScene();

private:
	scoped_ptr<GameRts_pimpl> pimpl;
};
