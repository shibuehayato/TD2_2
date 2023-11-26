#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include "DebugCamera.h"
#include "WorldTransform.h"
#include "FollowCamera.h"
#include "Enemy.h"
#include"Tower.h"
#include"OverheadCamera.h"

#include"ImGuiManager.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

    // 衝突判定と応答
	void CheckAllCollisions();

	// 敵発生
	void EnemyPop(Vector3 pos);

	// 敵発生データの読み込み
	void LoadEnemyPopData();

	// 敵発生コマンドの更新
	void UpdateEnemyCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデルデータ
	std::unique_ptr<Model> model_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	std::unique_ptr<Player> player_;
	// 3Dモデルの生成
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	// 敵キャラ
	//Enemy* enemy_ = nullptr;
	// 3Dモデルの生成
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm;
	std::unique_ptr<Model> modelEnemyR_arm;

	std::list<std::unique_ptr<Enemy>> enemies_;

	// 天球
	std::unique_ptr<Skydome> skydome_;

	// 3Dモデルの生成
	std::unique_ptr<Model> modelSkydome_;

	// 地面
	std::unique_ptr<Ground> ground_;

	// 3Dモデルの生成
	std::unique_ptr<Model> modelGround_;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;
	//タワーの生成
	std::unique_ptr<Tower> tower_;
	std::unique_ptr<Model> modeltower_;

	std::unique_ptr<OverheadCamera> overheadCamera_;
	bool isOverheadCameraActive_ = false;



	int32_t cameracooltime_;
	bool cameracooltimeActive_ = false;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	XINPUT_STATE prevjoyState;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	// 待機中フラグ
	bool isWaiting_;
	// 待機タイマー
	int32_t waitTimer_;

	// シーン切り替え
	enum Scene { TITLE, OPERATION, GAME, CLEAR, GAMEOVER };
	Scene scene = TITLE;
	// テクスチャハンドル
	uint32_t TitleTexture_ = 0;
	uint32_t OperationTexture_ = 0;
	uint32_t ClearTexture_ = 0;
	uint32_t GameoverTexture_ = 0;
	// シーン画面のスプライト
	std::unique_ptr<Sprite> TitleSprite_ = nullptr;
	std::unique_ptr<Sprite> OperationSprite_ = nullptr;
	std::unique_ptr<Sprite> ClearSprite_ = nullptr;
	std::unique_ptr<Sprite> GameoverSprite_ = nullptr;

	// タワーHpテクスチャハンドル
	uint32_t TowerHp5Texture_ = 0;
	uint32_t TowerHp4Texture_ = 0;
	uint32_t TowerHp3Texture_ = 0;
	uint32_t TowerHp2Texture_ = 0;
	uint32_t TowerHp1Texture_ = 0;
	// タワーHpのスプライト
	std::unique_ptr<Sprite> TowerHp5Sprite_ = nullptr;
	std::unique_ptr<Sprite> TowerHp4Sprite_ = nullptr;
	std::unique_ptr<Sprite> TowerHp3Sprite_ = nullptr;
	std::unique_ptr<Sprite> TowerHp2Sprite_ = nullptr;
	std::unique_ptr<Sprite> TowerHp1Sprite_ = nullptr;

	// クリアまでのタイマー
	int ClearTimer_ = 0;

	// タワーhp
	int TowerHp_ = 5;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
