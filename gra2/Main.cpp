#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <functional>

using namespace std;

class Button {
public:
    Button() = default;

    Button(const std::string& label, const sf::Font& font, float x, float y) {
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);

        sf::FloatRect bounds = text.getGlobalBounds();
        buttonRect.setSize(sf::Vector2f(bounds.width + 20, bounds.height + 20));
        buttonRect.setPosition(x - 10, y - 10);
        buttonRect.setFillColor(sf::Color::Black);
        buttonRect.setOutlineColor(sf::Color::White);
        buttonRect.setOutlineThickness(2);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(buttonRect);
        window.draw(text);
    }

    bool isClicked(sf::Vector2i mousePos) const {
        return buttonRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void setText(const std::string& label) {
        text.setString(label);
        sf::FloatRect bounds = text.getGlobalBounds();
        buttonRect.setSize(sf::Vector2f(bounds.width + 20, bounds.height + 20));
    }

    void setPosition(float x, float y) {
        text.setPosition(x, y);
        sf::FloatRect bounds = text.getGlobalBounds();
        buttonRect.setPosition(x - 10, y - 10);
    }

    sf::FloatRect getGlobalBounds() const {
        return buttonRect.getGlobalBounds();
    }

private:
    sf::Text text;
    sf::RectangleShape buttonRect;
};

class Player {
public:
    Player();
    void displayInventory(sf::RenderWindow& window, const sf::Font& font) const;
    void addItem(const std::string& item);
    void upgradeTool(const std::string& tool);
    void save(std::ostream& saveStream) const;
    void load(std::istream& loadStream);
    int getHealth() const;
    void takeDamage(int damage);
    void heal(int amount);
    int attack() const;
    int specialAttack();
    void defend();
    void increaseMaxHealth(int amount);
    int getMaxHealth() const;
    void reset();
    void displayHealth(sf::RenderWindow& window, const sf::Font& font) const;
    void resetSpecialAttack();

private:
    std::vector<std::string> inventory;
    std::map<std::string, int> tools;
    int health;
    int maxHealth;
    bool specialAttackUsed;
    bool defending;
};

void Player::resetSpecialAttack() {
    specialAttackUsed = false;
}

Player::Player() : health(100), maxHealth(100), specialAttackUsed(false), defending(false) {
    tools["waz"] = 1;
    tools["gasnica"] = 1;
    tools["bomba wodna"] = 1;
}

void Player::displayInventory(sf::RenderWindow& window, const sf::Font& font) const {
    std::string inventoryText = "Ekwipunek:\n";
    for (const auto& item : inventory) {
        inventoryText += "- " + item + "\n";
    }
    inventoryText += "Narzedzia:\n";
    for (const auto& tool : tools) {
        inventoryText += "- " + tool.first + ": poziom " + std::to_string(tool.second) + "\n";
    }
    inventoryText += "Zdrowie: " + std::to_string(health) + " / " + std::to_string(maxHealth) + "\n";

    Button inventoryButton(inventoryText, font, 10, 10);
    inventoryButton.draw(window);
}

void Player::addItem(const std::string& item) {
    inventory.push_back(item);
}

void Player::upgradeTool(const std::string& tool) {
    if (tools.find(tool) != tools.end()) {
        tools[tool]++;
    }
}

void Player::save(std::ostream& saveStream) const {
    saveStream << inventory.size() << "\n";
    for (const auto& item : inventory) {
        saveStream << item << "\n";
    }
    saveStream << tools.size() << "\n";
    for (const auto& tool : tools) {
        saveStream << tool.first << " " << tool.second << "\n";
    }
    saveStream << health << "\n";
    saveStream << maxHealth << "\n";
}

void Player::load(std::istream& loadStream) {
    int inventorySize;
    loadStream >> inventorySize;
    inventory.clear();
    for (int i = 0; i < inventorySize; ++i) {
        std::string item;
        loadStream >> item;
        inventory.push_back(item);
    }
    int toolsSize;
    loadStream >> toolsSize;
    tools.clear();
    for (int i = 0; i < toolsSize; ++i) {
        std::string toolName;
        int toolLevel;
        loadStream >> toolName >> toolLevel;
        tools[toolName] = toolLevel;
    }
    loadStream >> health;
    loadStream >> maxHealth;
}

int Player::getHealth() const {
    return health;
}

void Player::takeDamage(int damage) {
    if (defending) {
        damage = static_cast<int>(damage * 0.3f);
        defending = false;
    }
    health -= damage;
    if (health < 0) health = 0;
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

int Player::attack() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(25, 35);
    return dis(gen);
}

int Player::specialAttack() {
    if (specialAttackUsed) {
        return 0;
    }
    specialAttackUsed = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(40, 70);
    return dis(gen);
}

void Player::defend() {
    defending = true;
}

void Player::increaseMaxHealth(int amount) {
    maxHealth += amount;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::reset() {
    inventory.clear();
    tools.clear();
    tools["waz"] = 1;
    tools["gasnica"] = 1;
    tools["bomba wodna"] = 1;
    health = maxHealth = 100;
    specialAttackUsed = false;
    defending = false;
}

void Player::displayHealth(sf::RenderWindow& window, const sf::Font& font) const {
    std::string healthText = "Zdrowie: " + std::to_string(health) + " / " + std::to_string(maxHealth);
    Button healthButton(healthText, font, 10, 10);
    healthButton.draw(window);
}

class Dragon {
public:
    Dragon(const std::string& name, const std::string& ability, int strength, int health, int minDamage, int maxDamage, int specialMinDamage, int specialMaxDamage);
    void displayDragonInfo(sf::RenderWindow& window, const sf::Font& font) const;
    void displayHealth(sf::RenderWindow& window, const sf::Font& font) const;
    std::string getName() const;
    int getHealth() const;
    void takeDamage(int damage);
    void attackPlayer(Player& player);
    int specialAttack();
    void defend();
    void performAction(Player& player, std::vector<std::string>& messages);
    bool isSpecialAttackUsed() const;
    void resetSpecialAttack();
    void resetHealth();

private:
    std::string name;
    std::string ability;
    int strength;
    int health;
    int initialHealth;
    int minDamage;
    int maxDamage;
    int specialMinDamage;
    int specialMaxDamage;
    bool specialAttackUsed;
    bool defending;
};

void Dragon::resetSpecialAttack() {
    specialAttackUsed = false;
}

void Dragon::resetHealth() {
    health = initialHealth;
}

Dragon::Dragon(const std::string& name, const std::string& ability, int strength, int health, int minDamage, int maxDamage, int specialMinDamage, int specialMaxDamage)
    : name(name), ability(ability), strength(strength), health(health), initialHealth(health), minDamage(minDamage), maxDamage(maxDamage), specialMinDamage(specialMinDamage), specialMaxDamage(specialMaxDamage), specialAttackUsed(false), defending(false) {}

void Dragon::displayDragonInfo(sf::RenderWindow& window, const sf::Font& font) const {
    std::string dragonInfo = "Imie smoka: " + name + "\n";
    dragonInfo += "Zdolnosc: " + ability + "\n";
    dragonInfo += "Sila: " + std::to_string(strength) + "\n";
    dragonInfo += "Zdrowie: " + std::to_string(health) + "\n";

    Button dragonInfoButton(dragonInfo, font, 10, 200);
    dragonInfoButton.draw(window);
}

void Dragon::displayHealth(sf::RenderWindow& window, const sf::Font& font) const {
    std::string healthText = "Zdrowie smoka: " + std::to_string(health);
    Button healthButton(healthText, font, window.getSize().x - 230, 10);
    healthButton.draw(window);
}

std::string Dragon::getName() const {
    return name;
}

int Dragon::getHealth() const {
    return health;
}

void Dragon::takeDamage(int damage) {
    if (defending) {
        damage = static_cast<int>(damage * 0.3f);
        defending = false;
    }
    health -= damage;
    if (health < 0) health = 0;
}

void Dragon::attackPlayer(Player& player) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minDamage, maxDamage);
    int damage = dis(gen);
    player.takeDamage(damage);
}

int Dragon::specialAttack() {
    if (specialAttackUsed) {
        return 0;
    }
    specialAttackUsed = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(specialMinDamage, specialMaxDamage);
    return dis(gen);
}

void Dragon::defend() {
    defending = true;
}

void Dragon::performAction(Player& player, std::vector<std::string>& messages) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4);

    int action = dis(gen);

    if (action < 2) {
        attackPlayer(player);
        messages.push_back("Smok atakuje gracza.");
    }
    else if (action < 4) {
        defend();
        messages.push_back("Smok sie broni.");
    }
    else {
        int damage = specialAttack();
        if (damage > 0) {
            player.takeDamage(damage);
            messages.push_back("Smok uzywa ataku specjalnego.");
        }
        else {
            messages.push_back("Smok probuje uzyc ataku specjalnego, ale jest juz wykorzystany.");
        }
    }
}

bool Dragon::isSpecialAttackUsed() const {
    return specialAttackUsed;
}

class Location {
public:
    Location(const std::string& name, const std::string& description);
    void displayLocationInfo(sf::RenderWindow& window, const sf::Font& font) const;
    std::string getName() const;
    bool solvePuzzle(Player& player, sf::RenderWindow& window, const sf::Font& font, std::string& playerAnswer, bool& solvingPuzzle, std::vector<std::string>& messages);
    void exploreLocation(sf::RenderWindow& window, const sf::Font& font, Player& player, std::function<Dragon& ()> getWeakestDragon, std::string& playerAnswer, bool& solvingPuzzle, bool& playerTurn, std::vector<std::string>& messages);
    void clearPuzzleText();

private:
    std::string name;
    std::string description;
    std::set<int> usedPuzzles;
    void drawScene(sf::RenderWindow& window) const;
    Button questionButton;
    Button answerButton;
};


void Location::clearPuzzleText() {
    questionButton.setText("");
    answerButton.setText("");
}

Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Location::displayLocationInfo(sf::RenderWindow& window, const sf::Font& font) const {
    std::string locationInfo = "Lokalizacja: " + name + "\n";
    locationInfo += "Opis: " + description + "\n";

    Button locationInfoButton(locationInfo, font, 10, 300);
    locationInfoButton.draw(window);
}

std::string Location::getName() const {
    return name;
}

bool Location::solvePuzzle(Player& player, sf::RenderWindow& window, const sf::Font& font, std::string& playerAnswer, bool& solvingPuzzle, std::vector<std::string>& messages) {
    std::vector<std::pair<std::string, std::string>> puzzles = {
        {"Co ma glowe, a nie ma oczu?", "glowka kapusty"},
        {"Co ma szyje, ale nie ma glowy?", "butelka"},
        {"Co biegnie, ale nie ma nog?", "rzeka"},
        {"Co rosnie, ale nie ma zycia?", "ciasto"}
    };

    if (usedPuzzles.size() == puzzles.size()) {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, puzzles.size() - 1);
    int randomIndex;
    do {
        randomIndex = dis(gen);
    } while (usedPuzzles.find(randomIndex) != usedPuzzles.end());

    usedPuzzles.insert(randomIndex);

    std::string question = puzzles[randomIndex].first;
    std::string correctAnswer = puzzles[randomIndex].second;

    questionButton = Button(question, font, 10, 450);
    answerButton = Button("", font, 10, 500);

    bool puzzleSolved = false;
    playerAnswer.clear();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b') {
                        if (!playerAnswer.empty())
                            playerAnswer.pop_back();
                    }
                    else if (enteredChar == '\r') {
                        if (playerAnswer == correctAnswer) {
                            player.increaseMaxHealth(10);
                            player.heal(10);
                            messages.push_back("Poprawna odpowiedz! Zyskujesz 10 punktow maksymalnego zdrowia i 10 punktow zdrowia.");
                            puzzleSolved = true;
                        }
                        else {
                            messages.push_back("Zla odpowiedz, napotykasz smoka!");
                            solvingPuzzle = false;
                            clearPuzzleText();
                            return false;
                        }
                        solvingPuzzle = false;
                        clearPuzzleText();
                        return puzzleSolved;
                    }
                    else if (std::isprint(enteredChar)) {
                        playerAnswer += enteredChar;
                    }
                }
            }
        }

        answerButton.setText("Odpowiedz: " + playerAnswer);

        window.clear();
        drawScene(window);
        questionButton.draw(window);
        answerButton.draw(window);
        window.display();
    }

    return puzzleSolved;
}

void Location::exploreLocation(sf::RenderWindow& window, const sf::Font& font, Player& player, std::function<Dragon& ()> getWeakestDragon, std::string& playerAnswer, bool& solvingPuzzle, bool& playerTurn, std::vector<std::string>& messages) {
    displayLocationInfo(window, font);
    for (int i = 0; i < 4; ++i) {
        if (solvePuzzle(player, window, font, playerAnswer, solvingPuzzle, messages)) {
            messages.push_back("Mozesz kontynuowac eksploracje.");
        }
        else {
            playerAnswer = "Bledna odpowiedz! Teraz musisz walczyc ze smokiem.";
            solvingPuzzle = false;
            Dragon& weakestDragon = getWeakestDragon();
            weakestDragon.attackPlayer(player);
            playerTurn = true;
            return;
        }
        clearPuzzleText(); // Clear the puzzle text after each puzzle attempt
    }
}

void Location::drawScene(sf::RenderWindow& window) const {
    window.clear();
    window.display();
}

class Game {
public:
    Game();
    void run();
    void handleEnding(int endingOption);
    void displayFinalConfrontationResult(bool won);

private:
    void showIntroduction();
    void showMenu();
    void handleInput(int option);
    void saveGame();
    void loadGame();
    void explore();
    void rescueMission();
    void finalConfrontation();
    void fightDragon(Dragon& dragon);
    void displayText(const std::string& message);
    void clearMessages();
    void handleClick(int x, int y);
    void handlePuzzleInput(sf::Event& event);
    void drawScene();
    Dragon& getRandomDragon();
    void displayPostBattle(bool won);
    void resetGame();
    void resetDragons();
    void returnToStart();
    void clearTurnMessages();
    void displayRescueMissionText(const std::string& message);
    void displayRescueCount(); // Nowa metoda

    Player player;
    int gameState;
    int explorationCount;
    bool inBattle;
    bool postBattle;
    bool battleWon;
    bool showEndGameButtons;
    std::vector<Location> locations;
    std::vector<Dragon> dragons;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::vector<Button> menuButtons;
    std::vector<Button> fightButtons;
    std::vector<Button> postBattleButtons;
    std::vector<Button> endGameButtons;
    Button retryButton;
    std::vector<std::string> messages;
    std::string playerAnswer;
    bool solvingPuzzle;
    bool playerTurn;
    Dragon* currentDragon;
    int rescueCount; // Nowa zmienna
};
Game::Game() : window(sf::VideoMode(800, 600), "Gra Przygodowa"), gameState(0), explorationCount(0), inBattle(false), postBattle(false), battleWon(false), showEndGameButtons(false), solvingPuzzle(false), playerAnswer(""), playerTurn(true), currentDragon(nullptr), rescueCount(0) {
    locations.emplace_back("Pyroklas", "Tetniace zyciem miasto znane z czestych obserwacji smokow i pozarow.");
    locations.emplace_back("Wulkaniczne Gory", "Niebezpieczny obszar, w ktorym rzekomo mieszka Wladca zaru.");

    dragons.emplace_back("Plomienny Pazur", "Ognisty Oddech", 5, 100, 20, 30, 40, 50);
    dragons.emplace_back("Dymna Skora", "Dymna Zaslona", 3, 90, 20, 25, 35, 45);
    dragons.emplace_back("Burzowe Skrzydlo", "Manipulacja Pogoda", 4, 100, 20, 30, 40, 50);
    dragons.emplace_back("Wladca zaru", "Ognista furia", 6, 150, 25, 35, 50, 60);

    if (!font.loadFromFile("C:/Users/grego/source/repos/Project4/Project4/fonts/Cour.ttf")) {
        std::cerr << "Nie mozna zaladowac czcionki Cour.ttf" << std::endl;
        exit(1);
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    float menuYPos = 50;
    menuButtons.emplace_back("1. Eksploruj", font, 10, menuYPos);
    menuYPos += 40;
    menuButtons.emplace_back("2. Misja ratunkowa", font, 10, menuYPos);
    menuYPos += 40;
    menuButtons.emplace_back("3. Ostateczna konfrontacja", font, 10, menuYPos);
    menuYPos += 40;
    menuButtons.emplace_back("4. Zapisz gre", font, 10, menuYPos);
    menuYPos += 40;
    menuButtons.emplace_back("5. Wczytaj gre", font, 10, menuYPos);
    menuYPos += 40;
    menuButtons.emplace_back("6. Wyjdz", font, 10, menuYPos);

    float fightYPos = 50;
    fightButtons.emplace_back("Atakuj", font, 10, fightYPos);
    fightYPos += 40;
    fightButtons.emplace_back("Obrona", font, 10, fightYPos);
    fightYPos += 40;
    fightButtons.emplace_back("Wylecz", font, 10, fightYPos);
    fightYPos += 40;
    fightButtons.emplace_back("Specjalny atak", font, 10, fightYPos);

    postBattleButtons.emplace_back("Zostan bohaterem miasta", font, 10, 300);
    postBattleButtons.emplace_back("Opusc miasto", font, 10, 350);
    postBattleButtons.emplace_back("Poszukaj nowych przygod", font, 10, 400);

    endGameButtons.emplace_back("Zacznij gre od nowa", font, window.getSize().x / 2.f - 75, window.getSize().y / 2.f + 30);

    retryButton = Button("Sprobuj ponownie", font, window.getSize().x / 2.f - 75, window.getSize().y / 2.f + 30);

    showIntroduction();
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (solvingPuzzle) {
                handlePuzzleInput(event);
            }
            else {
                if (event.type == sf::Event::MouseButtonPressed) {
                    handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear();
        drawScene();
        window.display();
    }
}

void Game::drawScene() {
    if (inBattle) {
        player.displayHealth(window, font);
        if (currentDragon != nullptr) {
            currentDragon->displayHealth(window, font);
        }
        float yOffset = 200;
        for (const auto& message : messages) {
            text.setString(message);
            text.setPosition(10, yOffset);
            window.draw(text);
            yOffset += 30;
        }
    }
    else {
        float yOffset = 10;
        for (const auto& message : messages) {
            text.setString(message);
            text.setPosition(10, yOffset);
            window.draw(text);
            yOffset += 30;
        }
    }

    if (postBattle) {
        if (!battleWon) {
            text.setPosition(window.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, window.getSize().y / 2.f - text.getGlobalBounds().height / 2.f - 30);
            window.draw(text);
            retryButton.draw(window);
        }
        else {
            for (const auto& button : postBattleButtons) {
                button.draw(window);
            }
        }
    }
    else if (inBattle) {
        for (const auto& button : fightButtons) {
            button.draw(window);
        }
    }
    else if (solvingPuzzle) {
    }
    else if (showEndGameButtons) {
        for (const auto& button : endGameButtons) {
            button.draw(window);
        }
    }
    else {
        for (const auto& button : menuButtons) {
            button.draw(window);
        }
    }

    displayRescueCount(); // Wywo³anie metody wyœwietlaj¹cej licznik uratowanych cywilów
}


void Game::clearMessages() {
    messages.clear();
}

void Game::clearTurnMessages() {
    if (!playerTurn) {
        clearMessages();
    }
}

void Game::showIntroduction() {
    clearMessages();
    displayText("Witaj w grze przygodowej!\nJestes czlonkiem elitarnej Brygady Skrzydla Ognia.\nTwoja misja jest ochrona miasta Pyroklas przed atakami smokow.\n");
    showMenu();
}

void Game::showMenu() {
    clearMessages();
}

void Game::handleInput(int option) {
    clearMessages();
    switch (option) {
    case 1:
        explore();
        break;
    case 2:
        rescueMission();
        break;
    case 3:
        finalConfrontation();
        break;
    case 4:
        saveGame();
        break;
    case 5:
        loadGame();
        break;
    case 6:
        window.close();
        break;
    default:
        displayText("Nieprawidlowa akcja.\n");
        break;
    }
    showMenu();
}

void Game::handleClick(int x, int y) {
    sf::Vector2i mousePos(x, y);

    if (postBattle) {
        if (!battleWon && retryButton.isClicked(mousePos)) {
            resetGame();
            return;
        }
        for (size_t i = 0; i < postBattleButtons.size(); ++i) {
            if (postBattleButtons[i].isClicked(mousePos)) {
                handleEnding(i);
                return;
            }
        }
    }
    else if (inBattle) {
        if (playerTurn) {
            clearTurnMessages();
            for (size_t i = 0; i < fightButtons.size(); ++i) {
                if (fightButtons[i].isClicked(mousePos)) {
                    switch (i) {
                    case 0: {
                        int damage = player.attack();
                        if (currentDragon != nullptr) {
                            currentDragon->takeDamage(damage);
                            messages.push_back("Gracz zaatakowal smoka, zadajac " + std::to_string(damage) + " obrazen.");
                            if (currentDragon->getHealth() <= 0) {
                                displayText("Pokonales smoka!\n");
                                inBattle = false;
                                if (currentDragon == &dragons[3]) {
                                    battleWon = true;
                                }
                                else {
                                    returnToStart();
                                }
                                currentDragon = nullptr;
                                return;
                            }
                        }
                        break;
                    }
                    case 1: {
                        player.defend();
                        messages.push_back("Gracz broni sie.");
                        break;
                    }
                    case 2: {
                        player.heal(20 + (std::rand() % 11));
                        messages.push_back("Gracz wyleczyl sie.");
                        break;
                    }
                    case 3: {
                        int damage = player.specialAttack();
                        if (damage > 0 && currentDragon != nullptr) {
                            currentDragon->takeDamage(damage);
                            messages.push_back("Gracz uzyl specjalnego ataku, zadajac " + std::to_string(damage) + " obrazen.");
                            if (currentDragon->getHealth() <= 0) {
                                displayText("Pokonales smoka!\n");
                                inBattle = false;
                                if (currentDragon == &dragons[3]) {
                                    battleWon = true;
                                }
                                else {
                                    returnToStart();
                                }
                                currentDragon = nullptr;
                                return;
                            }
                        }
                        else {
                            messages.push_back("Umiejetnosc specjalna juz zostala uzta.");
                        }
                        break;
                    }
                    default:
                        break;
                    }

                    window.clear();
                    drawScene();
                    window.display();

                    playerTurn = false;
                    break;
                }
            }

            if (currentDragon != nullptr && currentDragon->getHealth() > 0) {
                currentDragon->performAction(player, messages);

                if (player.getHealth() <= 0) {
                    displayText("Przegrales.\n");
                    inBattle = false;
                    if (currentDragon == &dragons[3]) {
                        displayPostBattle(false);
                    }
                    else {
                        returnToStart();
                    }
                    currentDragon = nullptr;
                    return;
                }

                playerTurn = true;
            }

            window.clear();
            drawScene();
            window.display();
        }
    }
    else if (solvingPuzzle) {
    }
    else if (showEndGameButtons) {
        for (size_t i = 0; i < endGameButtons.size(); ++i) {
            if (endGameButtons[i].isClicked(mousePos)) {
                resetGame();
                return;
            }
        }
    }
    else {
        for (size_t i = 0; i < menuButtons.size(); ++i) {
            if (menuButtons[i].isClicked(mousePos)) {
                handleInput(i + 1);
                break;
            }
        }
    }
}


void Game::handleEnding(int endingOption) {
    clearMessages();
    switch (endingOption) {
    case 0:
        displayText("Brawo! Zostales bohaterem miasta Pyroklas i stales sie jego ikona.");
        break;
    case 1:
        displayText("Opuszczasz miasto Pyroklas w celu spokojnego zycia na odludziu.");
        break;
    case 2:
        displayText("Decydujesz sie kontynuowac swoje przygody. Rozpoczynasz nowa misje z aktualnym zdrowiem.");
        returnToStart();
        return;
    default:
        displayText("Nieznana opcja koncowa.");
        break;
    }
    showEndGameButtons = true;
    postBattle = false;
}

void Game::handlePuzzleInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            char enteredChar = static_cast<char>(event.text.unicode);
            if (enteredChar == '\b') {
                if (!playerAnswer.empty())
                    playerAnswer.pop_back();
            }
            else if (enteredChar == '\r') {
                solvingPuzzle = false;
            }
            else if (std::isprint(enteredChar)) {
                playerAnswer += enteredChar;
            }
        }
    }
}

void Game::displayRescueMissionText(const std::string& message) {
    messages.push_back(message);
    drawScene();
}

void Game::displayRescueCount() {
    std::string rescueText = "Uratowani cywile: " + std::to_string(rescueCount);
    sf::Text rescueDisplay(rescueText, font, 20);
    rescueDisplay.setFillColor(sf::Color::White);
    rescueDisplay.setPosition(10, window.getSize().y - 30);
    window.draw(rescueDisplay);
}



void Game::rescueMission() {
    clearMessages();
    displayRescueMissionText("Rozpoczynasz misje ratunkowa.\n");
    displayRescueMissionText("Musisz uratowac mieszkancow miasta przed atakiem smoka.\n");

    std::vector<std::string> tasks = {
        "Uratuj dzieci z plonacego budynku.",
        "Odnajdz zaginionego strazaka w lesie.",
        "Zabezpiecz most przed zawaleniem sie.",
        "Pomoz rannym mieszkanca w ewakuacji."
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tasks.size() - 1);
    int taskIndex = dis(gen);

    displayRescueMissionText("Zadanie: " + tasks[taskIndex]);

    int rescueChance = std::rand() % 100;
    if (rescueChance < 50) {
        displayRescueMissionText("Misja nieudana! Smok zaatakowal mieszkancow, musisz walczyc ze smokiem.\n");
        Dragon& dragon = getRandomDragon();
        fightDragon(dragon);
    }
    else {
        displayRescueMissionText("Misja udana! Uratowales mieszkancow miasta.\n");
        rescueCount++; // Zwiêkszenie licznika uratowanych cywilów

        std::uniform_int_distribution<> rewardDis(0, 1);
        int rewardType = rewardDis(gen);

        switch (rewardType) {
        case 0:
            player.increaseMaxHealth(20);
            displayRescueMissionText("Nagroda: Zwiekszenie maksymalnego zdrowia o 20 punktow.");
            break;
        case 1:
            player.heal(50);
            displayRescueMissionText("Nagroda: Wyleczenie o 50 punktow zdrowia.");
            break;
        }

        player.addItem("Nagroda od mieszkancow");
        player.upgradeTool("waz");
        displayRescueMissionText("Zdobyles dodatkowy ekwipunek i ulepszyles narzedzia!");
    }
}



void Game::saveGame() {
    try {
        std::ofstream file("savegame.txt");
        if (!file) throw std::runtime_error("Blad otwarcia pliku.");
        file << gameState << "\n";
        file << explorationCount << "\n";
        player.save(file);
        file.close();
        displayText("Gra zapisana.\n");
    }
    catch (const std::exception& e) {
        displayText(e.what());
    }
}

void Game::loadGame() {
    try {
        std::ifstream file("savegame.txt");
        if (!file) throw std::runtime_error("Brak pliku zapisu.");
        file >> gameState;
        file >> explorationCount;
        player.load(file);
        file.close();
        displayText("Gra wczytana.\n");
    }
    catch (const std::exception& e) {
        displayText(e.what());
    }
}

void Game::returnToStart() {
    inBattle = false;
    postBattle = false;
    showEndGameButtons = false;
    clearMessages();
    displayText("Wracasz do poczatkowego ekranu gry.");
    showMenu();
}

void Game::explore() {
    if (explorationCount >= 1) {
        displayText("Wykorzystales swoja jedyna mozliwosc eksploracji.\n");
        return;
    }
    explorationCount++;
    displayText("Eksplorujesz teren.\n");
    for (auto& location : locations) {
        location.exploreLocation(window, font, player, std::bind(&Game::getRandomDragon, this), playerAnswer, solvingPuzzle, playerTurn, messages);
        if (solvingPuzzle) {
            displayText("Rozwiazujesz zagadke...\n");
            return;
        }
        else if (!solvingPuzzle && playerAnswer == "Bledna odpowiedz! Teraz musisz walczyc ze smokiem.") {
            player.resetSpecialAttack();
            Dragon& dragon = getRandomDragon();
            fightDragon(dragon);
            return;
        }
    }
    displayText("Udalo Ci sie ukonczyc eksploracje bez walki ze smokiem!\n");
}

void Game::displayFinalConfrontationResult(bool won) {
    if (won) {
        displayText("Pokonales Wladce zaru! Miasto Pyroklas jest bezpieczne.\n");
        displayText("Wybierz swoja nastepna przygode:\n");
        postBattle = true;
        battleWon = true;
    }
    else {
        displayText("Zostales pokonany przez Wladce zaru. Miasto Pyroklas jest zniszczone.\n");
        displayPostBattle(false);
    }
}

void Game::finalConfrontation() {
    displayText("Konfrontujesz sie z Wladca zaru w epickiej bitwie.\n");
    player.resetSpecialAttack();
    fightDragon(dragons[3]);

    if (player.getHealth() > 0) {
        displayFinalConfrontationResult(true);
    }
    else {
        displayFinalConfrontationResult(false);
    }
}

void Game::fightDragon(Dragon& dragon) {
    inBattle = true;
    currentDragon = &dragon;
    clearMessages();
    displayText("Walczysz ze smokiem!\n");

    player.resetSpecialAttack();
    currentDragon->resetSpecialAttack();

    while (dragon.getHealth() > 0 && player.getHealth() > 0) {
        window.clear();
        drawScene();
        window.display();

        if (playerTurn) {
            sf::Event event;
            while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                    for (size_t i = 0; i < fightButtons.size(); ++i) {
                        if (fightButtons[i].isClicked(mousePos)) {
                            switch (i) {
                            case 0: {
                                int damage = player.attack();
                                if (currentDragon != nullptr) {
                                    currentDragon->takeDamage(damage);
                                    messages.push_back("Gracz zaatakowal smoka, zadajac " + std::to_string(damage) + " obrazen.");
                                    if (currentDragon->getHealth() <= 0) {
                                        displayText("Pokonales smoka!\n");
                                        inBattle = false;
                                        if (currentDragon == &dragons[3]) {
                                            displayFinalConfrontationResult(true);
                                        }
                                        else {
                                            returnToStart();
                                        }
                                        currentDragon = nullptr;
                                        return;
                                    }
                                }
                                break;
                            }
                            case 1: {
                                player.defend();
                                messages.push_back("Gracz broni sie.");
                                break;
                            }
                            case 2: {
                                player.heal(20 + (std::rand() % 11));
                                messages.push_back("Gracz wyleczyl sie.");
                                break;
                            }
                            case 3: {
                                int damage = player.specialAttack();
                                if (damage > 0 && currentDragon != nullptr) {
                                    currentDragon->takeDamage(damage);
                                    messages.push_back("Gracz uzyl specjalnego ataku, zadajac " + std::to_string(damage) + " obrazen.");
                                    if (currentDragon->getHealth() <= 0) {
                                        displayText("Pokonales smoka!\n");
                                        inBattle = false;
                                        if (currentDragon == &dragons[3]) {
                                            displayFinalConfrontationResult(true);
                                        }
                                        else {
                                            returnToStart();
                                        }
                                        currentDragon = nullptr;
                                        return;
                                    }
                                }
                                else {
                                    messages.push_back("Umiejetnosc specjalna juz zostala uzta.");
                                }
                                break;
                            }
                            default:
                                break;
                            }

                            window.clear();
                            drawScene();
                            window.display();

                            playerTurn = false;
                            break;
                        }
                    }

                    if (currentDragon != nullptr && currentDragon->getHealth() > 0) {
                        currentDragon->performAction(player, messages);

                        if (player.getHealth() <= 0) {
                            displayText("Przegrales.\n");
                            inBattle = false;
                            if (currentDragon == &dragons[3]) {
                                displayPostBattle(false);
                            }
                            else {
                                returnToStart();
                            }
                            currentDragon = nullptr;
                            return;
                        }

                        playerTurn = true;
                    }

                    window.clear();
                    drawScene();
                    window.display();
                }
            }
        }
    }
}

void Game::displayPostBattle(bool won) {
    postBattle = true;
    battleWon = won;
    clearMessages();
    if (won) {
        displayText("Gratulacje! Pokonales smoka!");
    }
    else {
        float textWidth = text.getGlobalBounds().width;
        float textHeight = text.getGlobalBounds().height;
        text.setString("Przegrales.");
        text.setPosition(window.getSize().x / 2.f - textWidth / 2.f, window.getSize().y / 2.f - textHeight / 2.f - 30);
        retryButton.setPosition(window.getSize().x / 2.f - retryButton.getGlobalBounds().width / 2.f, window.getSize().y / 2.f + textHeight / 2.f + 30);
        messages.push_back("Przegrales.");
    }
    drawScene();
}

void Game::resetGame() {
    player.reset();
    explorationCount = 0;
    inBattle = false;
    postBattle = false;
    battleWon = false;
    showEndGameButtons = false;
    playerTurn = true;
    resetDragons();
    clearMessages();
    displayText("Gra zresetowana. Zacznij od nowa.");
    showMenu();
}

void Game::resetDragons() {
    for (auto& dragon : dragons) {
        dragon.resetSpecialAttack();
        dragon.resetHealth();
    }
}

Dragon& Game::getRandomDragon() {
    std::vector<Dragon*> validDragons;
    for (auto& dragon : dragons) {
        if (dragon.getName() != "Wladca zaru") {
            validDragons.push_back(&dragon);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, validDragons.size() - 1);
    return *validDragons[dis(gen)];
}

void Game::displayText(const std::string& message) {
    messages.push_back(message);
    drawScene();
}

int main() {
    Game game;
    game.run();
    return 0;
}

