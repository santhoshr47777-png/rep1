#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::Music music;
    
    std::string path;
    std::cout << "Enter music file path: ";
    std::getline(std::cin, path);

    if (!music.openFromFile(path)) {
        std::cout << "Error: Could not open file!\n";
        return 1;
    }

    music.play();
    std::cout << "Playing... Press Enter to stop.\n";
    std::cin.get();
    music.stop();

    return 0;
}
