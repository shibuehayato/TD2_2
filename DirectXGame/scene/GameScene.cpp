#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

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
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get()
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
	modeltower_.reset(Model::CreateFromOBJ("tower", true));
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

	// 自キャラに追従カメラのビュープロジェクションをアドレス渡しする
	player_->SetViewProjection(&followCamera_->GetViewProjection());

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

		// 天球の更新
		skydome_->Update();

		// 地面の更新
		ground_->Update();

		// デバッグカメラの更新
		debugCamera_->Update();

		// タワーの更新
		tower_->Update();

		overheadCamera_->Update();

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
		} else {
			// 追従カメラの更新
			followCamera_->Update();
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
			viewProjection_.TransferMatrix();
		}

		CheckAllCollisions();

			if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
					scene = CLEAR;
				}
			}
		}
		break;

	case CLEAR: // クリアシーン
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
	//GameoverSprite_->Draw();

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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() 
{
	float towerRadius = 2.5f;
	float enemyRadius = 2.5f;

	// 判定対象AとBの座標
	Vector3 posA, posB;

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
		}
	}

	#pragma endregion
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
	enemies_.push_back(static_cast<std::unique_ptr<Enemy>>(enemy));
}

void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
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