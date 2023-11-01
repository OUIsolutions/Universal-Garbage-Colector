
privateUniversalComplexGarbageElement * newprivateUniversalGarbageElement(short type, void *value){
    privateUniversalComplexGarbageElement *self = (privateUniversalComplexGarbageElement*) malloc(sizeof(privateUniversalComplexGarbageElement));
    self->type = type;
    self->value = value;
    return  self;
}

