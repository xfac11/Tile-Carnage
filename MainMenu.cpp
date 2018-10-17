#include"MainMenu.h"

MainMenu::MainMenu(std::string fileName)
{
	this->upButton = false;
	this->downButton = false;
	this->currenttext = 0;
	this->state = StartTest;//=currenttext
	this->font.loadFromFile(fileName);
	this->text = new sf::Text[5];
	this->nrOftexts = 4;
	this->cap = 5;
	for (int i = 0; i < this->cap; i++)
	{
		this->text[i] = sf::Text();
		this->text[i].setFont(this->font);
	}
	this->text[0].setString("Start Test");
	this->text[1].setString("Edit world");
	this->text[2].setString("Options");
	this->text[3].setString("Exit");
}

MainMenu::MainMenu()
{
	fireBall = new Animate("fireBall", 6, 0.08f);
	//this->box.setFillColor(sf::Color(137,124,124));
	this->upButton = false;
	this->downButton = false;
	this->currenttext = 0;
	this->textForBox.loadFromFile("textures/MainMenuScreen_Shit.png");
	this->box.setTexture(this->textForBox);
	//this->box.setColor(sf::Color(100,100,100));
	this->state = StartTest;//=currenttext
	this->font.loadFromFile("Font/PressStart2P.ttf");
	this->text = new sf::Text[5];
	this->nrOftexts = 4;
	this->cap = 5;
	for (int i = 0; i < this->cap; i++)
	{
		this->text[i] = sf::Text();
		this->text[i].setFont(this->font);
	}
	this->text[0].setString("Start Test");
	this->text[1].setString("Edit World");
	this->text[2].setString("Options");
	this->text[3].setString("Exit");
}

MainMenu::~MainMenu()
{
	delete this->fireBall;
	delete[] this->text;
}

void MainMenu::addtext(std::string text)
{
	if (this->nrOftexts == this->cap)
	{
		this->cap += 5;
		sf::Text* temptext = new sf::Text[this->cap];
		for (int i = 0; i < this->nrOftexts; i++)
		{
			temptext[i] = this->text[i];
		}
		delete[] this->text;
		this->text = temptext;
	}
	this->text[this->nrOftexts] = sf::Text(text,this->font);
	this->nrOftexts++;
}

void MainMenu::changetext(Direction dir)
{
	this->text[this->currenttext].setFillColor(sf::Color::White);
	if (dir == DOWN)
	{
		if (currenttext == this->nrOftexts)
		{
			this->currenttext = 0;
			this->state = Selected(0);
		}
		else
		{
			this->currenttext++;
			this->state = Selected(this->currenttext);
		}
	}
	else if (dir == UP)
	{
		if (currenttext == 0)
		{
			
			this->currenttext = this->nrOftexts;
			this->state = Selected(this->currenttext);
		}
		else
		{
			this->currenttext--;
			this->state = Selected(this->currenttext);
		}
	}
	this->text[this->currenttext].setFillColor(sf::Color::Red);
}

void MainMenu::changetext()
{
	this->text[this->currenttext].setFillColor(sf::Color::White);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&this->downButton==false)
	{
		this->downButton = true;
		if (currenttext == this->nrOftexts-1)
		{
			
			this->currenttext = 0;
			this->state = Selected(this->currenttext);
		}
		else
		{
			this->currenttext++;
			this->state = Selected(this->currenttext);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

	}
	else
	{
		this->downButton = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&this->upButton==false)
	{
		this->upButton = true;
		if (currenttext == 0)
		{
			this->currenttext = this->nrOftexts-1;
			this->state = Selected(this->currenttext);
		}
		else
		{
			this->currenttext--;
			this->state = Selected(this->currenttext);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

	}
	else
	{
		this->upButton = false;
	}
	this->text[this->currenttext].setFillColor(sf::Color::Red);
	//std::cout << "menu:" << this->currenttext << std::endl;
}

void MainMenu::movementForFire(sf::RenderWindow & window, float deltaTime)
{
	int dir = rand() % 1920 + -1;

	this->fireBall->move(0, 200 * deltaTime);
	if (this->fireBall->getPosition().x > window.getSize().x - 000 || this->fireBall->getPosition().x<000 ||
		this->fireBall->getPosition().y >window.getSize().y - 000 || this->fireBall->getPosition().y < 000)
	{
		this->fireBall->setPosition(dir, 010);
	}
}

void MainMenu::drawtext(sf::RenderWindow & window,float deltaTime)
{
	//this->fireBall->movement(window);
	window.draw(box);
	this->fireBall->update(window, deltaTime);
	for (int i = 0; i < this->nrOftexts; i++)
	{
		window.draw(this->text[i]);
	}
	this->movementForFire(window,deltaTime);
}

void MainMenu::setPosition(sf::Vector2f pos,float space)
{
	float y = pos.y;
	int maxChars = 0;
	for (int i = 0; i < this->nrOftexts; i++)
	{
		sf::FloatRect textRect = text[i].getLocalBounds();
		text[i].setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		if (this->text[maxChars].getString().getSize() < this->text[i].getString().getSize())
		{
			maxChars = i;
		}
		this->text[i].setPosition(pos.x, y);
		this->text[i].setCharacterSize(40);
		y += this->text[i].getCharacterSize() + space;
	}
	//this->box.setSize(sf::Vector2f(31*this->text[maxChars].getString().getSize(), 10.0f+this->nrOftexts*this->text[0].getCharacterSize() + (this->nrOftexts - 1)*space));
	//this->box.setSize(sf::Vector2f(1920.0f, 1080.0f));
	this->box.setOrigin(sf::Vector2f(1920.0f/ 2, 1080.0f / 2));
	this->box.setPosition(pos.x , pos.y );

}

int MainMenu::getCurrenttext() const
{
	return this->currenttext;
}

Selected MainMenu::getCurrentSelected() const
{
	return this->state;
}
