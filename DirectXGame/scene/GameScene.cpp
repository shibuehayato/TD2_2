#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>
#include <algorithm>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// サウンドデータの読み込み
	bgmDataHandle_ = audio_->LoadWave("bgm.wav");
	clearSoundDataHandle_ = audio_->LoadWave("clear.wav");
	gameOverSoundDataHandle_ = audio_->LoadWave("GameOver.wav");

	TitleTexture_ = TextureManager::Load("scene/title.png");
	OperationTexture_ = TextureManager::Load("scene/operation.png");
	ClearTexture_ = TextureManager::Load("scene/clear.png");
	GameoverTexture_ = TextureManager::Load("scene/GameOver.png");

	TitleSprite_ = std::make_unique<Sprite>();
	OperationSprite_ = std::make_unique<Sprite>();
	ClearSprite_ = std::make_unique<Sprite>();
	GameoverSprite_ = std::make_unique<Sprite>();

	TitleSprite_.reset(Sprite::Create(TitleTexture_, {0, 0}));
	OperationSprite_.reset(Sprite::Create(OperationTexture_, {0, 0}));
	ClearSprite_.reset(Sprite::Create(ClearTexture_, {0, 0}));
	GameoverSprite_.reset(Sprite::Create(GameoverTexture_, {0, 0}));

	TowerHp5Texture_ = TextureManager::Load("towerHp/TowerHp5.png");
	TowerHp4Texture_ = TextureManager::Load("towerHp/TowerHp4.png");
	TowerHp3Texture_ = TextureManager::Load("towerHp/TowerHp3.png");
	TowerHp2Texture_ = TextureManager::Load("towerHp/TowerHp2.png");
	TowerHp1Texture_ = TextureManager::Load("towerHp/TowerHp1.png");

	TowerHp5Sprite_ = std::make_unique<Sprite>();
	TowerHp4Sprite_ = std::make_unique<Sprite>();
	TowerHp3Sprite_ = std::make_unique<Sprite>();
	TowerHp2Sprite_ = std::make_unique<Sprite>();
	TowerHp1Sprite_ = std::make_unique<Sprite>();

	TowerHp5Sprite_.reset(Sprite::Create(TowerHp5Texture_, {0, 0}));
	TowerHp4Sprite_.reset(Sprite::Create(TowerHp4Texture_, {0, 0}));
	TowerHp3Sprite_.reset(Sprite::Create(TowerHp3Texture_, {0, 0}));
	TowerHp2Sprite_.reset(Sprite::Create(TowerHp2Texture_, {0, 0}));
	TowerHp1Sprite_.reset(Sprite::Create(TowerHp1Texture_, {0, 0}));

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("sample.png");

	// 3Dモデルデータの生成
	model_.reset(Model::Create());

	// ビュープロジェクションの初期化
	viewProjection_.translation_ = {0, 1, -10};
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 3Dモデルの生成
	modelFighterHead_.reset(Model::CreateFromOBJ("2", true));
	modelFighterBody_.reset(Model::CreateFromOBJ("3", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("5", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("4", true));
	modelFighterMouth_.reset(Model::CreateFromOBJ("1", true));
	// 自キャラモデル
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
		modelFighterR_arm_.get(), modelFighterMouth_.get()
	};
	// 自キャラの初期化
	player_->Initialize(playerModels);

	// 敵キャラの生成
	//enemy = std::make_unique<Enemy>();
	// 3Dモデルの生成
	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_arm.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm.reset(Model::CreateFromOBJ("needle_R_arm", true));
	// 敵キャラのモデル
	std::vector<Model*> enemyModels = {
	    modelEnemyBody_.get(), modelEnemyL_arm.get(), modelEnemyR_arm.get()
	};
	//// 敵キャラの初期化
	//enemy_->Initialize(enemyModels);
	//// 敵キャラにゲームシーンを渡す
	//enemy_->SetGameScene(this); 



	// 3Dモデルの生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	// 天球の生成
	skydome_ = std::make_unique<Skydome>();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_.get());

	// 3Dモデルの生成
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 地面の初期化
	ground_->Initialize(modelGround_.get());

	// タワーの生成
	tower_ = std::make_unique<Tower>();
	// タワーの3Dモデルの生成
	modeltower_.reset(Model::CreateFromOBJ("tower2", true));
	// タワーの初期化
	tower_->Initialize(modeltower_.get());


	//Enemy* enemy = new Enemy();
	//enemy1 = new Enemy();
	//// 敵キャラの初期化
	//enemy1->Initialize(enemyModels);
	//// 敵キャラにゲームシーンを渡す
	//enemy1->SetGameScene(this); 
	//// 敵キャラにタワーのアドレスを渡す
	//enemy1->SetTower(tower_.get());
	//enemies_.push_back(static_cast<std::unique_ptr<Enemy>>(enemy1));
	
	// デバッグカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(2000, 2000);

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	// タイムリミットの生成
	TimeLimit_ = std::make_unique<TimeLimit>();
	TimeLimit_->Initialize();

	// 自キャラに追従カメラのビュープロジェクションをアドレス渡しする
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	ui_ = std::make_unique<UI>();
	ui_->Initialize();

	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	overheadCamera_ = std::make_unique<OverheadCamera>();
	overheadCamera_->Initialize();

	cameracooltime_ = 10;

	LoadEnemyPopData();

	
}

void GameScene::Update() {

	switch (scene) {
	case GameScene::TITLE: // タイトルシーン

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = OPERATION;
				}
			}
	 }
		break;
	case GameScene::OPERATION: // 操作説明
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = GAME;
				}
			}
		}
		break;
	case GameScene::GAME:

		if (!audio_->IsPlaying(voiceHandle_)) {

			voiceHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.5);
		}

		audio_->ResumeWave(voiceHandle_);

		ClearTimer_ -= 1;

		// 自キャラの更新
		player_->Update();

		// 敵キャラの更新
		// enemy_->Update();

		// for (const auto& enemy : enemies_) {
		//	enemy->Update();
		// }

		UpdateEnemyCommands();
		for (const std::unique_ptr<Enemy>& enemy : enemies_) {
			enemy->Update();
		}

		enemies_.remove_if([](std::unique_ptr<Enemy>& enemy) {
			if (enemy->IsDead()) {
				return true;
			}
			return false;
		});

		// 天球の更新
		skydome_->Update();

		// 地面の更新
		ground_->Update();

		// デバッグカメラの更新
		debugCamera_->Update();

		// タワーの更新
		tower_->Update();

		// タイムリミットの更新
		TimeLimit_->Update();

		overheadCamera_->Update();


	//UIの更新
	ui_->Update();
	


		if (Input::GetInstance()->GetJoystickState(0, joyState) && cameracooltime_ >= 10) {

			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
				isOverheadCameraActive_ = true;
			}
		}
		if (overheadCamera_->IsCameraActive()) {
			
			isOverheadCameraActive_ = false;
			
			cameracooltimeActive_ = true;
		}
		if (cameracooltimeActive_) {
			cameracooltime_--;
		}
		if (cameracooltime_ <= 0) {
			cameracooltime_ = 10;
			cameracooltimeActive_ = false;
		}

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_RETURN)) {
			isDebugCameraActive_ = true;
		}
#endif

		// カメラの処理
		if (isDebugCameraActive_) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			viewProjection_.TransferMatrix();
		} else if (isOverheadCameraActive_) {
			overheadCamera_->Timer();
			viewProjection_.matView = overheadCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = overheadCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		} else if(isOverheadCameraActive_==false) {
			// 追従カメラの更新
			followCamera_->Update();
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
			viewProjection_.TransferMatrix();
		}

		CheckAllCollisions();

		// クリア条件
		if (ClearTimer_ == 0) {
			scene = CLEAR;
		}
		// ゲームオーバー条件
		if (TowerHp_ == 0) {

			scene = GAMEOVER;
		}
		break;

	case CLEAR: // クリアシーン

		ClearTimer_ = 60*60;
		TowerHp_ = 5;
		TimeLimit_->Reset();
		audio_->PauseWave(voiceHandle_);

		for (const std::unique_ptr<Enemy>& enemy : enemies_) {
			enemy->OnCollision();
		}

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = TITLE;
				}
			}
		}
		break;
	case GAMEOVER: // ゲームオーバーシーン

		ClearTimer_ = 60*60;
		TowerHp_ = 5;
		TimeLimit_->Reset();
		audio_->PauseWave(voiceHandle_);

		for (const std::unique_ptr<Enemy>& enemy : enemies_) {
			enemy->OnCollision();
		}

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = TITLE;
				}
			}
		}
		break;

	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	if (scene == TITLE) {
		TitleSprite_->Draw();
	}
	if (scene == OPERATION) {
		OperationSprite_->Draw();
	}
	if (scene == CLEAR) {
		ClearSprite_->Draw();
	}
	if (scene == GAMEOVER) {
		GameoverSprite_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	if (scene == GAME) {
		// 自キャラの描画
		player_->Draw(viewProjection_);

		// 敵キャラの描画
		// enemy_->Draw(viewProjection_);
		for (const auto& enemy : enemies_) {
			enemy->Draw(viewProjection_);
		}

		// 天球の描画
		skydome_->Draw(viewProjection_);

		// 地面の描画
		ground_->Draw(viewProjection_);

		// タワーの描画
		tower_->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (scene == GAME) {
		if (TowerHp_ == 5) {
			TowerHp5Sprite_->Draw();
		}
		if (TowerHp_ == 4) {
			TowerHp4Sprite_->Draw();
		}
		if (TowerHp_ == 3) {
			TowerHp3Sprite_->Draw();
		}
		if (TowerHp_ == 2) {
			TowerHp2Sprite_->Draw();
		}
		if (TowerHp_ == 1) {
			TowerHp1Sprite_->Draw();
		}

		TimeLimit_->Draw();
		ui_->Draw();
	}



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() 
{
	float towerRadius = 2.5f;
	float enemyRadius = 1.0f;
	float pBulletRadius = 1.0f;
	float beamRadius = 20.0f;
	//float wallRadius = 20.0f;

	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	// ビームの取得
	const std::unique_ptr<Beam>& beam = player_->GetBeam();
	

	// 壁の取得
	//const std::unique_ptr<Wall>& wall = player_->GetWall();
	

	

	#pragma region 敵とタワーの当たり判定
	// タワーの座標
	posA = tower_->GetWorldPosition();

	// タワーと敵全ての当たり判定
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
	    // 敵の座標
		posB = enemy->GetWorldPosition();

		// 座標AとBの距離を求める
		Vector3 Distance = {
		    (posA.x - posB.x) * (posA.x - posB.x), (posA.y - posB.y) * (posA.y - posB.y),
		    (posA.z - posB.z) * (posA.z - posB.z)};

		if (Distance.x + Distance.y + Distance.z <=
			(towerRadius + enemyRadius) * (towerRadius + enemyRadius))
		{
			// 敵の衝突時コールバック関数を呼び出す
			enemy->OnCollision();
			TowerHp_ -= 1;
		}
	}
	#pragma endregion

	#pragma region 自弾と敵の当たり判定
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
		for (PlayerBullet* bullet : playerBullets) {
			posA = enemy->GetWorldPosition();
			posB = bullet->GetWorldPosition();

			  Vector3 Distance = {
			    (posA.x - posB.x) * (posA.x - posB.x), (posA.y - posB.y) * (posA.y - posB.y),
			    (posA.z - posB.z) * (posA.z - posB.z)};

			    if (Distance.x + Distance.y + Distance.z <=
			      (enemyRadius + pBulletRadius) * (enemyRadius + pBulletRadius)) {
				enemy->OnCollision();
				bullet->OnCollision();
			  }
		}
	}
	#pragma endregion

	#pragma region ビームと敵の当たり判定
	posA = player_->GetWorldPosition();
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
		
		
			
			 posB = enemy->GetWorldPosition();
		Vector3 closestPoint{
		    std::clamp(posB.x, posA.x-beamRadius, posA.x+beamRadius ), 
			std::clamp(posB.y, posA.y-beamRadius, posA.y+beamRadius ),
		    std::clamp(posB.z, posA.z-beamRadius, posA.z + beamRadius)};
		      float distance = Length(Subtract(posB, closestPoint));
			 /*  Vector3 Distance = {
		          (posA.x - posB.x) * (posA.x - posB.x), (posA.y - posB.y) * (posA.y - posB.y),
		          (posA.z - posB.z) * (posA.z - posB.z)};*/

			  if (distance<=enemyRadius &&
		          player_->IsdurationAlive()) {
				enemy->OnCollision();
				beam->OnCollision();
			  }
		
	}
#pragma endregion

//	#pragma region 壁と敵の当たり判定
//	posA = player_->GetWorldPosition();
//	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
//		     
//		      posB = enemy->GetWorldPosition();
//		      Vector3 closestPoint{
//		          std::clamp(posB.x, posA.x-10.0f, posA.x + wallRadius),
//		          std::clamp(posB.y, posA.y-10.0f, posA.y + wallRadius),
//		          std::clamp(posB.z, posA.z-10.0f, posA.z + wallRadius)};
//		      float distance = Length(Subtract(posB, closestPoint));
//			  /* Vector3 Distance = {
//		          (posA.x - posB.x) * (posA.x - posB.x), (posA.y - posB.y) * (posA.y - posB.y),
//		          (posA.z - posB.z) * (posA.z - posB.z)};*/
//		     
//		      if (distance<=enemyRadius-1.0f&&
//		           wall->IsTimer()) {
//			    enemy->SpeedOnCollision();
//			    wall->OnCollision();
//		      }
//			  if (wall->IsTimer() == false)
//			  {
//			    enemy->SpeedNoCollision();
//			  }
//			  
//	}
//#pragma endregion
	
}

void GameScene::EnemyPop(Vector3 pos)
{
	// 敵キャラのモデル
	std::vector<Model*> enemyModels = {
	    modelEnemyBody_.get(), modelEnemyL_arm.get(), modelEnemyR_arm.get()
	};
	Enemy* enemy = new Enemy();
	// 敵キャラの初期化
	enemy->Initialize(enemyModels,pos);
	// 敵キャラにゲームシーンを渡す
	enemy->SetGameScene(this);
	// 敵キャラにタワーのアドレスを渡す
	enemy->SetTower(tower_.get());
	enemy->SetPlayer(player_.get());
	enemies_.push_back(static_cast<std::unique_ptr<Enemy>>(enemy));
}

void GameScene::LoadEnemyPopData() {

	int i = 0;

	while (i < 2) {

		// ファイルを開く
		std::ifstream file;
		file.open("Resources/enemyPop.csv");
		assert(file.is_open());

		// ファイルの内容を文字列ストリームにコピー
		enemyPopCommands << file.rdbuf();
		file.close();
		if (i >= 2) {
			  i = 0;
		}
		i++;
	}
}

void GameScene::UpdateEnemyCommands() 
{
	// 待機処理
	if (isWaiting_) {
		  waitTimer_--;
		  if (waitTimer_ <= 0) {
			// 待機完了
			isWaiting_ = false;
		  }
		  return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		  // 1行分の文字列をストリームに変換して解析しやすくする
		  std::istringstream line_stream(line);

		  std::string word;
		  // ,区切りで行の先頭文字列を取得
		  getline(line_stream, word, ',');

		  // "//"から始まる行はコメント
		  if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		  }

		  // POPコマンド
		  if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			EnemyPop(Vector3(x, y, z));
		  }

		  // WAITコマンド
		  else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWaiting_ = true;
			waitTimer_ = waitTime;

			// コマンドループ
			break;
		  }
	}
}