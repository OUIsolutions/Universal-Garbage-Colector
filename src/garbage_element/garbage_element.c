
privateUniversalGarbageElement * newprivateUniversalGarbageElement(short type, void *value){
    privateUniversalGarbageElement *self = (privateUniversalGarbageElement*) malloc(sizeof(privateUniversalGarbageElement));
    self->type = type;
    self->value = value;
    return  self;
}

