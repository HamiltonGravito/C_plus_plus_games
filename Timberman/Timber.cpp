// Diretiva Include adiciona um conteúdo de outro arquivo no projeto (biblioteca) antes da compilação (pré-processamento) O .hpp indica que se trata de um arquivo de cabeçalho
#include <SFML/Graphics.hpp>

// E um álias para a classe SFML e assim ela não se confunde com outras classes
using namespace sf;

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
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/


		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Apaga o quadro anterior
		window.clear();

		// Desenha a cena do game
		window.draw(spriteBackground);

		// Alterna entre a superfície exibida anteriormente (cena anterior) e a recém-atualizada (buffer duplo)
		window.display();
	}
	return 0;
}