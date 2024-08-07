#pragma once
#include "Common.h"
#include "Entity.h"
#include "EntityManger.h"

struct PlayerConfig { size_t SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { size_t SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { size_t SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class GameEngine
{							
	sf::RenderWindow		m_window;
	unsigned int			m_width_window = 700;
	unsigned int			m_hight_window = 600;
	bool					m_is_paused = false;
	bool					m_is_running = true;
	PlayerConfig			m_player_config = {};
	EnemyConfig				m_enemy_config = {};
	BulletConfig			m_bullet_config = {};
	unsigned int			m_score = 0;
	bool					m_mode = 0;
	size_t					m_fps = 0;
	size_t					m_lastEnemySponed = 0;
	size_t					m_current_frame = 0;
	sf::Font				m_font;
	sf::Text				m_text;
	EntityManager			m_entities;

	std::shared_ptr<Entity> m_player;
	
	void init(const std::string&);

	void sRender();
	void sMovement();
	void sCollision();
	void SLifeSpan();
	void sUserInput();
	void sSpownSystem();
	
	void spownEnemy();
	void spownPlayer();
	void spownBullets();

public:
	GameEngine(const std::string&);
	void run();
};
