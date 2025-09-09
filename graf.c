#include  <gtk/gtk.h>
#include <stdio.h>

// Глобальные переменные для виджетов (или передавать через user_data)
GtkWidget *status_label = NULL;
guint timeout_id = 0;
const int the_time_when_the_text_about_saving_freezes = 5;

// Функция скрытия статусного текста
gboolean hide_status_text(gpointer user_data) {
    gtk_label_set_text(GTK_LABEL(status_label), ""); // Очищаем текст
    timeout_id = 0; // Сбрасываем ID таймера
    return G_SOURCE_REMOVE; // Останавливаем таймер
}

// Функция-обработчик кнопки
void on_action_button_clicked(GtkButton *button, gpointer user_data) {
    // Показываем текст уведомления
    gtk_label_set_text(GTK_LABEL(status_label), "Выполняется действие...");
    
    // Если уже есть активный таймер - останавливаем его
    if (timeout_id > 0) {
        g_source_remove(timeout_id);
    }
    
    // Запускаем таймер на 5 секунд для скрытия текста
    timeout_id = g_timeout_add_seconds(the_time_when_the_text_about_saving_freezes, hide_status_text, NULL);
}

// Функция создания кнопки с статусным текстом
GtkWidget* create_action_button_with_status() {
    // Контейнер для кнопки и текста
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Статусный текст (сначала пустой)
    status_label = gtk_label_new("");
    gtk_widget_set_size_request(status_label, 150, -1); // Фиксированная ширина
    gtk_label_set_xalign(GTK_LABEL(status_label), 1.0); // Выравнивание по правому краю
    gtk_box_pack_start(GTK_BOX(hbox), status_label, TRUE, TRUE, 0);
    
    // Кнопка действия
    GtkWidget *button = gtk_button_new_with_label("Выполнить");
    g_signal_connect(button, "clicked", G_CALLBACK(on_action_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    
    return hbox;
}

// Функция создания выпадающего списка с подписью
GtkWidget* create_labeled_combo(const gchar *label_text, const gchar *option1, const gchar *option2) {
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(hbox, TRUE);
    
    // Подпись
    GtkWidget *label = gtk_label_new(label_text);
    gtk_widget_set_size_request(label, 80, -1);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    
    // Выпадающий список
    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), option1);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), option2);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0); // Выбираем первый элемент
    
    gtk_widget_set_hexpand(combo, TRUE);
    gtk_box_pack_start(GTK_BOX(hbox), combo, TRUE, TRUE, 0);
    
    return hbox;
}

// Функция создания текстового поля с подписью
GtkWidget* create_labeled_entry(const gchar *label_text, const gchar *default_text) {
    // Контейнер для подписи и поля
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    
    // ВКЛЮЧАЕМ РАСШИРЕНИЕ СЕТКИ
    //gtk_widget_set_hexpand(hbox, TRUE);
    //gtk_widget_set_vexpand(hbox, TRUE);
    //gtk_widget_set_halign(hbox, GTK_ALIGN_FILL);
    //gtk_widget_set_valign(hbox, GTK_ALIGN_FILL);

    // Подпись
    GtkWidget *label = gtk_label_new(label_text);
    gtk_widget_set_size_request(label, 80, -1); // Фиксированная ширина подписи
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    
    // Текстовое поле
    GtkWidget *entry = gtk_entry_new();
    if (default_text != NULL) {
        gtk_entry_set_text(GTK_ENTRY(entry), default_text);
    }
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    
    return hbox;
}

// Функция создания всех полей ввода
void create_input_fields(GtkWidget *container) {
    // Создаем сетку для аккуратного расположения
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);  // Отступ между строками
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5); // Отступ между колонками
    
    // Создаем 4 поля с подписями
    GtkWidget *field1 = create_labeled_entry("Подпись 1:", "");
    GtkWidget *field2 = create_labeled_entry("Подпись 2:", ""); 
    GtkWidget *field3 = create_labeled_entry("Подпись 3:", "");
    GtkWidget *field4 = create_labeled_entry("Подпись 4:", "");
    
    GtkWidget *combo = create_labeled_combo("Опция:", "Пункт 1", "Пункт 2");

    // Размещаем в сетке
    gtk_grid_attach(GTK_GRID(grid), field1, 0, 0, 1, 1); // column, row, width, height
    gtk_grid_attach(GTK_GRID(grid), field2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), field3, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), field4, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), combo, 0, 4, 1, 1);
    
    // КНОПКА СТАТУСА - добавляем на последнюю строку
    GtkWidget *button_row = create_action_button_with_status();
    gtk_grid_attach(GTK_GRID(grid), button_row, 0, 5, 1, 1);
    
    // Выравнивание кнопки справа
    gtk_widget_set_halign(button_row, GTK_ALIGN_END);
    // Добавляем сетку в контейнер
    gtk_container_add(GTK_CONTAINER(container), grid);
}

GtkWidget* create_aspect_container() {
    // Создаем контейнер с соотношением сторон 16:9
    GtkWidget *aspect_frame = gtk_aspect_frame_new("", 0.5, 0.5, 16.0/9.0, FALSE);
    
    // ВИЗУАЛЬНОЕ ВЫДЕЛЕНИЕ (для отладки)
    gtk_widget_set_name(aspect_frame, "aspect-container"); // CSS идентификатор
    
    // Устанавливаем минимальный размер
    gtk_widget_set_size_request(aspect_frame, 1600, 900); // Минимум 16:9
    gtk_frame_set_shadow_type(GTK_FRAME(aspect_frame), GTK_SHADOW_NONE);
    
    return aspect_frame;
}

void on_window_resize(GtkWidget *widget, GdkRectangle *allocation, gpointer data) {
    GtkWidget *container = (GtkWidget *)data;
    
    // Получаем текущий размер контейнера
    GtkAllocation container_alloc;
    gtk_widget_get_allocation(container, &container_alloc);
    
    //g_print("Размер окна: %dx%d | Размер контейнера: %dx%d\n",
    //       allocation->width, allocation->height,
    //       container_alloc.width, container_alloc.height);
}

void apply_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    const gchar *css = 
        "#aspect-container {"
        "   margin: 20px;"                            // Увеличим отступ
        "   padding: 20px;"                           // Добавим внутренний отступ
        "}"
        
        "label {"                                     // Стиль для всех подписей
        "   font-weight: bold;"
        "   color: #333;"
        "   min-width: 80px;"                         // Фиксированная ширина
        "}"
        
        "entry {"                                     // Стиль текстовых полей
        "   padding: 8px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   background: white;"
        "}"
        
        "entry:focus {"                               // Стиль при фокусе
        "   border-color: #4a90e2;"
        "   box-shadow: 0 0 0 2px rgba(74, 144, 226, 0.2);"
        "}"
        
        "combobox {"                                  // Стиль выпадающего списка
        "   padding: 5px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   background: white;"
        "}"
        
        "combobox:focus {"
        "   border-color: #4a90e2;"
        "   box-shadow: 0 0 0 2px rgwba(74, 144, 226, 0.2);"
        "}"
        
        "combobox arrow {"
        "   color: #666;"
        "}";
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

int main(int argc, char *argv[]) {
    read_file();
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Адаптивный контейнер");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    apply_css();

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_set_halign(main_box, GTK_ALIGN_CENTER);  // Центр по горизонтали
    gtk_widget_set_valign(main_box, GTK_ALIGN_CENTER);
    // Создаем адаптивный контейнер
    //GtkWidget *container = create_aspect_container();
    //gtk_box_pack_start(GTK_BOX(main_box), container, TRUE, TRUE, 0);

    
    GtkWidget *gribs = create_aspect_container();
    gtk_box_pack_start(GTK_BOX(main_box), gribs, TRUE,TRUE, 0);
    g_signal_connect(window, "size-allocate", G_CALLBACK(on_window_resize), gribs);

    create_input_fields(gribs);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}