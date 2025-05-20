// Diretiva Include adiciona um conteúdo de outro arquivo no projeto (biblioteca) antes da compilação (pré-processamento) O .hpp indica que se trata de um arquivo de cabeçalho
#include <SFML/Graphics.hpp>
// E um álias para a classe SFML e assim ela não se confunde com outras classes
using namespace sf;
#include <sstream>

// Classe principal do jogo (aplicativo)
int main()
{
	// Cria um objeto chamado vm da classe VideoMode e os parâmetros representam a resolução da tela do jogador
	VideoMode vm(1920, 1080);

	// Renderiza uma tela (fullscren) com o título Timber
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Cria um objeto Texture que armazena uma imagem na GPU - Demora para carregar na GPU mas depois de carregadas seu acesso é muito rápido
	Texture textureBackground;

	// Carrega uma imagem (url) para a GPU
	textureBackground.loadFromFile("graphics/background.png");

	// Cria um sprite 
	Sprite spriteBackground;

	// Associa um objeto Sprite a um Texture
	spriteBackground.setTexture(textureBackground);

	// Seta as coordenadas do spriteBackground nesse caso (0,0 - canto superior esquerdo)
    spriteBackground.setPosition(0,0);

    // Preparando o troco de árvore
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Preparar abelha
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    // Preparar nuvens
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    // Time bar
    RectangleShape timeBar; //Desenha retangulos simples
    float timeBarStartWidth = 400;
    float timeBarHeight = 40;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


    bool paused = true;
    int score = 0;
    Text messageText;
    Text scoreText;
    // Carrega uma fonte externa
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    // Adiciona propriedades aos Textos
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to Start!");
    scoreText.setString("Score = 0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Posiciona os Textos
    FloatRect textRect = messageText.getLocalBounds(); // Retangulo com coordenadas de ponto flutuante
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920/ 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

	while (window.isOpen())
	{

        // Captura eventos do SO (fechar janela, toques do teclado ou movimentações do mouse e etc), pois, se esses eventos não forem processados o SO acredita que o sistema travou e não está respondendo
        Event event;
        while (window.pollEvent(event)){
            // Evento para fechar a janela (clicar no X)
            if (event.type == Event::Closed)
                window.close();
        }

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		// Verifica se a tecla ESC foio pressionada
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}
        if (Keyboard::isKeyPressed(Keyboard::Return)){
            paused = false;
            score = 0;
            timeRemaining = 6;
        }

		/*
		****************************************
		Update the scene
		****************************************
		*/
        if(!paused){
            //Tratando a barra de tempo
            Time dt = clock.restart();
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if(timeRemaining <= 0.0f){
                paused = true;
                messageText.setString("Out of time!!!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920/2.0f, 1080/2.0f);
            }
            if (!beeActive){
                srand((int) time(0));
                beeSpeed = (rand() % 100) + 100;
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            } else {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
                if(spriteBee.getPosition().x < -100){
                    beeActive = false;
                }
            }

            if (!cloud1Active) {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            } else {
                spriteCloud1.setPosition(
                    spriteCloud1.getPosition().x +
                    (cloud1Speed * dt.asSeconds()),
                    spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x > 1920){
                    cloud1Active = false;
                }
            }

            if (!cloud2Active) {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                srand((int)time(0) * 20);
                float height = ((rand() % 300) - 150);
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            } else {
                spriteCloud2.setPosition(
                    spriteCloud2.getPosition().x +
                    (cloud2Speed * dt.asSeconds()),
                    spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x > 1920){
                    cloud2Active = false;
                }
            }

            if (!cloud3Active) {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);
                srand((int)time(0) * 30);
                float height = ((rand() % 450) - 150);
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            } else {
                spriteCloud3.setPosition(
                    spriteCloud3.getPosition().x +
                    (cloud3Speed * dt.asSeconds()),
                    spriteCloud3.getPosition().y);
                if (spriteCloud3.getPosition().x > 1920){
                    cloud3Active = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Apaga o quadro anterior
		window.clear();

		// Desenha a cena do game (Cada sprite é desenhado na ordem de inserção)
		window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);
        if(paused){
            window.draw(messageText);
        }

		// Alterna entre a superfície exibida anteriormente (cena anterior) e a recém-atualizada (buffer duplo)
		window.display();
	}
	return 0;
}