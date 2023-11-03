
/**
 * @brief Initializes all 64 color combinations.
 */
void init_colors();

/**
 * @brief Saves the current color. Can be restored via a call to restore_color
 */
void save_color();

/**
 * @brief Restores the color to whatever the last saved color was.
 */
void restore_color();

/**
 * @brief Set the fg color object
 * 
 * @param color The color to set to
 */
void set_fg_color(int color);

/**
 * @brief Set the bg color object
 * 
 * @param color The color to set to
 */
void set_bg_color(int color);

/**
 * @brief Set the color pair object
 * 
 * @param fg_color Foreground color
 * @param bg_color Background color
 */
void set_color_pair(int fg_color, int bg_color);

/**
 * @brief Reverses the foreground and background colors.
 */
void reverse_color();

/**
 * @brief Set the color object
 * 
 * @param color The exact color pair to set to.
 */
void set_color(int color);