

UniversalGarbage newUniversalGarbage(void (*clear_callback)(short type, void*value)){
    UniversalGarbage self = {0};
    self.clear_callback = clear_callback;
    self.is_main_a_normal_value = true;
    self.normal_values = malloc(0);
    self.especial_values = malloc(0);
    return self;
}