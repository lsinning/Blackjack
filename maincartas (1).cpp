#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Representa una carta
class Card {
public:
    string suit;
    string rank;
    int value;

    Card(string s, string r, int v) : suit(s), rank(r), value(v) {}
};

// Representa el mazo de cartas
class Deck {
private:
    vector<Card> deck;

public:
    Deck() {
        string suits[] = {"Corazones", "Diamantes", "Tréboles", "Espadas"};
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

        for (const auto& suit : suits) {
            for (int i = 0; i < 13; i++) {
                deck.push_back(Card(suit, ranks[i], values[i]));
            }
        }
    }

    void shuffle() {
        srand(time(0));
        for (int i = 0; i < deck.size(); i++) {
            int randIndex = rand() % deck.size();
            swap(deck[i], deck[randIndex]);
        }
    }

    Card dealCard() {
        Card card = deck.back();
        deck.pop_back();
        return card;
    }

    int remainingCards() {
        return deck.size();
    }
};

// Representa a un jugador
class Player {
public:
    string name;
    vector<Card> hand;
    int score;

    Player(string n) : name(n), score(0) {}

    void addCard(Card card) {
        hand.push_back(card);
        score += card.value;
    }

    void displayHand() {
        cout << name << " tiene las cartas: ";
        for (auto& card : hand) {
            cout << card.rank << " de " << card.suit << " | ";
        }
        cout << " Puntaje: " << score << endl;
    }

    bool isBusted() {
        return score > 21;
    }

    void resetHand() {
        hand.clear();
        score = 0;
    }
};

// Clase que gestiona el juego
class Game {
private:
    Deck deck;
    vector<Player> players;

public:
    Game(int numPlayers) {
        deck.shuffle();
        for (int i = 0; i < numPlayers; i++) {
            string name;
            cout << "Ingresa el nombre del jugador " << i + 1 << ": ";
            cin >> name;
            players.push_back(Player(name));
        }
    }

    void playRound() {
        // Repartir dos cartas a cada jugador
        for (auto& player : players) {
            player.addCard(deck.dealCard());
            player.addCard(deck.dealCard());
        }

        // Mostrar las manos de los jugadores
        for (auto& player : players) {
            player.displayHand();
        }

        // Turno de cada jugador
        for (auto& player : players) {
            while (true) {
                char choice;
                cout << player.name << ", ¿Quieres otra carta? (s/n): ";
                cin >> choice;
                if (choice == 's' || choice == 'S') {
                    player.addCard(deck.dealCard());
                    player.displayHand();
                    if (player.isBusted()) {
                        cout << player.name << " ¡Se ha pasado! Puntaje: " << player.score << endl;
                        break;
                    }
                } else {
                    break;
                }
            }
        }

        // Determinar ganador
        int highestScore = 0;
        string winner;
        for (auto& player : players) {
            if (!player.isBusted() && player.score > highestScore) {
                highestScore = player.score;
                winner = player.name;
            }
        }

        if (winner.empty()) {
            cout << "Nadie ganó esta ronda." << endl;
        } else {
            cout << "El ganador es " << winner << " con un puntaje de " << highestScore << endl;
        }

        // Resetear las manos de los jugadores para la siguiente ronda
        for (auto& player : players) {
            player.resetHand();
        }
    }

    void start() {
        while (deck.remainingCards() > 0) {
            playRound();
            char continueGame;
            cout << "¿Quieres jugar otra ronda? (s/n): ";
            cin >> continueGame;
            if (continueGame == 'n' || continueGame == 'N') {
                break;
            }
        }
        cout << "Fin del juego. ¡Gracias por jugar!" << endl;
    }
};

// Función principal
int main() {
    int numPlayers;
    cout << "¿Cuántos jugadores? ";
    cin >> numPlayers;
    Game game(numPlayers);
    game.start();
    return 0;
}
