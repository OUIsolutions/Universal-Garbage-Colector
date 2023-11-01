
privateUniversalGarbageComplexElement * newprivateUniversalGarbageElement(short type, void *value){
    privateUniversalGarbageComplexElement *self = (privateUniversalGarbageComplexElement*) malloc(sizeof(privateUniversalGarbageComplexElement));
    self->type = type;
    self->value = value;
    return  self;
}

