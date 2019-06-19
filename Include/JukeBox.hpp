/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @file Music singleton
 */

#ifndef JUKEBOX_HPP
#define JUKEBOX_HPP

#include <map>
#include <boost/filesystem.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

/**
 * @remark Sound are used for small effect, music for background music
 */
class JukeBox {
public:
    static JukeBox &getInstance();
    bool addMusic(const std::string &name, const std::string &fileName);
    bool addSound(const std::string &name, const std::string &fileName);
    void playMusic(const std::string &name);
    void playSound(const std::string &name);
    void pauseMusic(const std::string &name);
    void setVolumeMusic(const float &volume);
    void setVolumeSound(const float &volume);

private:
    JukeBox();
    ~JukeBox() = default;
    JukeBox& operator=(const JukeBox&) = delete;
    JukeBox(const JukeBox&) = delete;
    void deleteEndOfSound();

private:
    static JukeBox jukeboxInstance;
    std::map<std::string, sf::Music> musicMap;
    std::map<std::string, sf::SoundBuffer> bufferMap;
    std::list<sf::Sound> soundList;
    float musicVolume;
    float soundVolume;
};

#endif /* !JUKEBOX_HPP */
