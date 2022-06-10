#file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# Players
configure_file ("cleric.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("knight.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("archer.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Enemies
configure_file ("enemy.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Backgrounds and utility
configure_file ("plain.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("select.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Skills
configure_file ("skills/heal.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/shield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/swing.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/clericShield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/barrage.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/apolloarrow.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/aimedshot.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/debilitate.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/intimidate.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/drainlife.png" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("skills/clericBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/archerBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/knightBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/witchBasic.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Fonts
configure_file ("amatic.ttf" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("titillium.otf" ${CMAKE_BINARY_DIR} COPYONLY)

# Effects
configure_file ("healEffect.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Projectiles
configure_file ("healProj.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Levels file
configure_file ("Levels.txt" ${CMAKE_BINARY_DIR} COPYONLY)

# Menu
configure_file ("MenuImages/menuBG.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/currentLevelIcon.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/levelSelection.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/levelCompleted.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/startButton.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("MenuImages/startButtonHL.png" ${CMAKE_BINARY_DIR} COPYONLY)
