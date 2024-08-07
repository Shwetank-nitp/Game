#include "Common.h"
#include "GameEngine.h"

GameEngine::GameEngine(const std::string& config)
{
	GameEngine::init(config);
}

void GameEngine::init(const std::string& string)
{
	std::ifstream fin(string);
	if (!fin)
	{
		std::cerr << "File not found!" << std::endl;
		exit(-1);
	}

	if(!m_font.loadFromFile("C://Users//Shwetank Rai//Desktop//KillerTech.ttf"))
	{
		std::cout << "Font not found!" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setPosition(1, 1);
	m_text.setString("Score");
	srand(time(0));

	std::string token;
	while (fin >> token)
	{
		if (token == "Window")
		{
			if (!(fin >> m_width_window >> m_hight_window >> m_fps >> m_mode))
			{
				std::cout << "Player Config error!" << std::endl;
				exit(-1);
			}

			m_window.setFramerateLimit(m_fps);

			if (m_mode) // 1/true = full_screen 
			{
				auto desktop = sf::VideoMode::getDesktopMode();
				m_window.create(sf::VideoMode(desktop), "dom0_full_screen");
			}
			else
			{
				m_window.create(sf::VideoMode(m_width_window, m_hight_window), "Under_testing_mode");
			}

		}
		else if (token == "Player")
		{
			if (!(fin >> m_player_config.SR >> m_player_config.CR >> m_player_config.S >> m_player_config.FR >> m_player_config.FG >> m_player_config.FB >> m_player_config.OR >> m_player_config.OG >> m_player_config.OB >> m_player_config.OT >> m_player_config.V))
			{
				std::cout << "Player Config error!" << std::endl;
				exit(-1);
			}
		}
		else if (token == "Enemy")
		{
			if (!(fin >> m_enemy_config.SR >> m_enemy_config.CR >> m_enemy_config.SMIN >> m_enemy_config.SMAX >> m_enemy_config.OR >> m_enemy_config.OG >> m_enemy_config.OB >> m_enemy_config.OT >> m_enemy_config.VMIN >> m_enemy_config.VMAX >> m_enemy_config.L >> m_enemy_config.SI))
			{
				std::cout << "Enemy Config error!" << std::endl;
				exit(-1);
			}
		}
		else if (token == "Bullet")
		{
			if (!(fin >> m_bullet_config.SR >> m_bullet_config.CR >> m_bullet_config.S >> m_bullet_config.FR >> m_bullet_config.FG >> m_bullet_config.FB >> m_bullet_config.OR >> m_bullet_config.OG >> m_bullet_config.OB >> m_bullet_config.OT >> m_bullet_config.V >> m_bullet_config.L))
			{
				std::cout << "Bollet Config error!" << std::endl;
				exit(-1);
			}
		}
	}
}

void GameEngine::sRender()
{
	m_window.clear();

	for (const auto& e : m_entities.get_entities())
	{
		m_window.draw(e->c_shape->shape);
	}
	m_window.draw(m_text);
	m_window.display();

}

void GameEngine::spownPlayer()
{
	m_player = m_entities.add_entites(Tags::PLAYER);

	//set player position.
	CTransform transform(Vec2(300, 200), Vec2(0, 0), 0);
	m_player->c_tansform = std::make_shared<CTransform>(transform);

	sf::Color fill_color(m_player_config.FR, m_player_config.FG, m_player_config.FB);
	sf::Color outer_color(m_player_config.OR, m_player_config.OG, m_player_config.OB);
	CShape shape(m_player_config.CR, m_player_config.V, m_player_config.OT, fill_color, outer_color);
	m_player->c_shape = std::make_shared<CShape>(shape);

	CCollision col(m_player_config.CR);
	m_player->c_collision = std::make_shared<CCollision>(col);

	CInput input;
	m_player->c_input = std::make_shared<CInput>(input);
}

void GameEngine::sUserInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_is_running = false;
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::A)
			{
				m_player->c_input->left = true;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				m_player->c_input->down = true;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				m_player->c_input->right = true;
			}
			if (event.key.code == sf::Keyboard::W)
			{
				m_player->c_input->up = true;
			}
			if (event.key.code == sf::Keyboard::P)
			{
				m_is_paused = true;
			}
			if (event.key.code == sf::Keyboard::R)
			{
				m_is_paused = false;
			}
			break;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::A)
			{
				m_player->c_input->left = false;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				m_player->c_input->down = false;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				m_player->c_input->right = false;
			}
			if (event.key.code == sf::Keyboard::W)
			{
				m_player->c_input->up = false;
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left && !m_player->c_input->mouse_left)
			{
				m_player->c_input->mouse_left = true;
			}
			if (event.mouseButton.button == sf::Mouse::Right && !m_player->c_input->mouse_right)
			{
				m_player->c_input->mouse_right = true;
			}

			std::cout << sf::Mouse::getPosition(m_window).y << std::endl;

			m_player->c_input->direction.x = sf::Mouse::getPosition(m_window).x;
			m_player->c_input->direction.y = sf::Mouse::getPosition(m_window).y;
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_player->c_input->mouse_left = false;
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_player->c_input->mouse_right = false;
			}
		default:
			break;
		}
	}
}

void GameEngine::sMovement()
{
	if (m_player->c_input->left) { m_player->c_tansform->velocity.x = -m_player_config.S; }
	if (m_player->c_input->right) { m_player->c_tansform->velocity.x = m_player_config.S; }
	if (m_player->c_input->up) { m_player->c_tansform->velocity.y = -m_player_config.S; }
	if (m_player->c_input->down) { m_player->c_tansform->velocity.y = m_player_config.S; }

	for (const auto& item : m_entities.get_entities())
	{
		if (item->c_tansform)
		{
			item->c_shape->shape.setPosition(item->c_tansform->pos.x, item->c_tansform->pos.y);
			item->c_shape->shape.setRotation(item->c_tansform->angle);
			item->c_tansform->angle += 0.11f;
			item->c_tansform->pos.add(item->c_tansform->velocity);
		}
		if (item->tag() == Tags::PLAYER)
		{
			m_player->c_tansform->velocity = { 0.0f, 0.0f };
		}
	}
}

void GameEngine::sCollision()
{
	// collision with block
	for (const auto& item : m_entities.get_entities())
	{
		if (item->c_tansform)
		{
			const Vec2 pos(item->c_tansform->pos.x, item->c_tansform->pos.y);
			const unsigned int c_rad = item->c_collision->radius;

			if (pos.x + c_rad >= m_window.getSize().x || pos.x - c_rad <= 0)
			{
				item->c_tansform->velocity >> 1; // change the velocity coordinate to -x
			}
			if (pos.y + c_rad >= m_window.getSize().y || pos.y - c_rad <= 0)
			{
				item->c_tansform->velocity >> 0; // change the velocity coordinate to -y
			}
		}
	}
	//Entity - Entity Collision
	for (auto& item : m_entities.get_entities())
	{
		if (item->c_tansform)
		{
			for (auto& o_item : m_entities.get_entities())
			{
				if (o_item == item)
				{
					continue;
				}

				const Vec2 diff = item->c_tansform->pos - o_item->c_tansform->pos;

				if (diff.lenght() <= item->c_collision->radius + o_item->c_collision->radius)
				{
					o_item->distroy();
					item->distroy();

					if (item->tag() == Tags::BULLET && o_item->tag() == Tags::ENEMRY)
					{
						++m_score;
						m_text.setString("Score : "+std::to_string(m_score));
					}
					//TODO : SPWOEN SMALLER ENEMEIES;
				}
			}
		}
	}

	//player wall collision condition:
	const Vec2 pos = m_player->c_tansform->pos;
	const unsigned int rad = m_player->c_collision->radius;
	if (pos.x <= rad)
	{
		m_player->c_tansform->pos.x = rad;
	}
	else if (pos.x >= m_window.getSize().x - rad)
	{
		m_player->c_tansform->pos.x = m_window.getSize().x - rad;
	}
	if (pos.y <= rad)
	{
		m_player->c_tansform->pos.y = rad;
	}
	else if (pos.y + rad >= m_window.getSize().y)
	{
		m_player->c_tansform->pos.y = m_window.getSize().y - rad;
	}
}

void GameEngine::spownEnemy()
{
	auto e = m_entities.add_entites(Tags::ENEMRY); // add_enemy_entity

	CCollision collision(m_enemy_config.CR);
	e->c_collision = std::make_shared<CCollision>(collision);

	const unsigned int rad = m_enemy_config.CR;
	const size_t points = std::rand() % (m_enemy_config.VMAX - m_enemy_config.VMIN + 1) + m_enemy_config.VMIN;
	float speed = std::rand() % (int)(m_enemy_config.SMAX - m_enemy_config.SMIN + 1) + m_enemy_config.SMIN;

	const float angle = std::rand() + 0.1f;
	Vec2 velocity(std::sin(angle), std::cos(angle));
	velocity.scale(speed);

	Vec2 pos(std::rand() % (int)(m_window.getSize().x - 2 * rad + 1) + rad, std::rand() % (int)(m_window.getSize().y - 2 * rad + 1));

	const sf::Color outline_color(std::rand() % (226), std::rand() % 226, std::rand() % 226);
	const sf::Color fill_color(std::rand() % (226), std::rand() % 226, std::rand() % 226);

	CShape shape(rad, m_enemy_config.OT, points, fill_color, outline_color);
	e->c_shape = std::make_shared<CShape>(shape);

	e->c_tansform = std::make_shared<CTransform>(CTransform(pos, velocity, 0));

	m_lastEnemySponed = m_current_frame;

}

void GameEngine::SLifeSpan()
{
	//remove dead entities
	m_entities.remove_dead_enitites();

	// delete the dead player entity
	if (!m_player->isActive())
	{
		m_player.reset();
	}

	//	Making enities dead based on there life remainiang.
	for (auto& item : m_entities.get_entities())
	{
		if (item->c_lifespan && item->c_lifespan->lifetime_remaning <= 0)
		{
			item->distroy();
		}
		else if (item->c_lifespan)
		{
			float alpha = static_cast<float>
				((item->c_lifespan->lifetime_remaning) / (item->c_lifespan->lifetime_remaning));

			sf::Color fill_color{ static_cast<sf::Uint8>(m_bullet_config.FR), static_cast<sf::Uint8>(m_bullet_config.FB), static_cast<sf::Uint8>(m_bullet_config.FG), static_cast<sf::Uint8>(alpha * 255.0f) };
			sf::Color outer_color{ static_cast<sf::Uint8>(m_bullet_config.OR), static_cast<sf::Uint8>(m_bullet_config.OB), static_cast<sf::Uint8>(m_bullet_config.OG), static_cast<sf::Uint8>(alpha * 255.0f) };

			item->c_shape->shape.setFillColor(fill_color);
			item->c_shape->shape.setOutlineColor(outer_color);

			--item->c_lifespan->lifetime_remaning;
		}
	}

}

void GameEngine::sSpownSystem()
{
	if (!m_player)
	{
		spownPlayer();
	}
	if (m_current_frame - m_lastEnemySponed >= (m_enemy_config.SI) * m_fps)
	{
		spownEnemy();
	}
	if (m_player->c_input->mouse_left)
	{
		spownBullets();
		m_player->c_input->mouse_left = false;
	}
}


void GameEngine::spownBullets()
{
	auto e = m_entities.add_entites(Tags::BULLET);
	e->c_collision = std::make_shared<CCollision>(CCollision(m_bullet_config.CR));
	e->c_lifespan = std::make_shared<CLifeTime>(CLifeTime(m_bullet_config.L * m_fps));

	float x = m_player->c_input->direction.x;
	float y = m_player->c_input->direction.y;

	Vec2 relative_vec{ x - m_player->c_tansform->pos.x, y - m_player->c_tansform->pos.y };
	relative_vec.unit();
	std::cout << relative_vec.x << " " << relative_vec.y << std::endl;
	float pos_mag = m_player->c_collision->radius + e->c_collision->radius + 0.5f;
	Vec2 pos{ pos_mag * relative_vec.x, pos_mag * relative_vec.y };
	pos.add(m_player->c_tansform->pos);
	Vec2 vel{ m_bullet_config.S * relative_vec.x, m_bullet_config.S * relative_vec.y };

	sf::Color fill_color;
	fill_color.r = m_bullet_config.FR;
	fill_color.g = m_bullet_config.FG;
	fill_color.b = m_bullet_config.FB;
	sf::Color outer_color;
	outer_color.r = m_bullet_config.OR;
	outer_color.g = m_bullet_config.OG;
	outer_color.b = m_bullet_config.OB;

	e->c_shape = std::make_shared<CShape>(CShape(m_bullet_config.SR, m_bullet_config.OT, m_bullet_config.V, fill_color, outer_color));
	e->c_tansform = std::make_shared<CTransform>(CTransform(pos, vel, 0));
}


void GameEngine::run()
{
	while (m_is_running)
	{
		if (!m_is_paused)
		{
			m_entities.update();
			sSpownSystem();
			sMovement();
			sCollision();
			SLifeSpan();
		}
		sUserInput();
		sRender();

		++m_current_frame;
	}
}
