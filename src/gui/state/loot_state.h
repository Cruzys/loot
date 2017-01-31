/*  LOOT

    A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
    Fallout: New Vegas.

    Copyright (C) 2014-2016    WrinklyNinja

    This file is part of LOOT.

    LOOT is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LOOT is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LOOT.  If not, see
    <https://www.gnu.org/licenses/>.
    */

#ifndef LOOT_BACKEND_APP_LOOT_STATE
#define LOOT_BACKEND_APP_LOOT_STATE

#include "gui/state/loot_settings.h"
#include "gui/state/game.h"

namespace loot {
class LootState : public LootSettings {
public:
  LootState();

  void load(YAML::Node& settings);
  void init(const std::string& cmdLineGame);
  const std::vector<std::string>& getInitErrors() const;

  void save(const boost::filesystem::path& file);

  gui::Game& getCurrentGame();
  void changeGame(const std::string& newGameFolder);

  // Get the folder names of the installed games.
  std::vector<std::string> getInstalledGames() const;

  bool hasUnappliedChanges() const;
  void incrementUnappliedChangeCounter();
  void decrementUnappliedChangeCounter();
private:
  // Select initial game.
  void selectGame(std::string cmdLineGame);
  void enableDebugLogging(bool enable);

  void updateCurrentGamePathSetting();

  static std::list<gui::Game> toGames(const std::vector<GameSettings>& settings);
  static std::vector<GameSettings> toGameSettings(const std::list<gui::Game>& games);

  std::list<gui::Game> installedGames_;
  std::list<gui::Game>::iterator currentGame_;
  std::vector<std::string> initErrors_;

  // Used to check if LOOT has unaccepted sorting or metadata changes on quit.
  size_t unappliedChangeCounter_;

  // Mutex used to protect access to member variables.
  std::mutex mutex_;
};
}

#endif