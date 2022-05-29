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
configure_file ("menuBG.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Skills
configure_file ("skills/heal.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/shield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/swing.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/clericShield.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/barrage.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("skills/apolloarrow.png" ${CMAKE_BINARY_DIR} COPYONLY)

# Fonts
configure_file ("amatic.ttf" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("titillium.otf" ${CMAKE_BINARY_DIR} COPYONLY)

