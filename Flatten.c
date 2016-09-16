#include "ruby.h"

// Defining a space for information and references about the module to be stored internally
VALUE Flatten = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_flatten();

VALUE method_flatten(VALUE self, VALUE args) {
	FILE *f = fopen("clog.txt", "w");
	if (f == NULL) {
		printf("no log file found\n");
		exit(1);
	}

	long len = RARRAY_LEN(self);
	VALUE result = rb_ary_new();
	VALUE stack = rb_ary_new();

	fprintf(f, "len: %lu\n", len);
	fprintf(f, "array: %s\n", RSTRING_PTR(rb_ary_to_s(self)));

	rb_ary_push(stack,self);
	while(RARRAY_LEN(stack) > 0) {
		VALUE array = rb_ary_pop(stack);
		long i;
		for(i = 0; i < RARRAY_LEN(array); i++) {
			VALUE e = RARRAY_AREF(array,i);
			switch (TYPE(e)) {
				case T_ARRAY:
					rb_ary_push(stack, e);
					break;
				default:
					if (rb_block_given_p()) {
						e = rb_yield(e);
					}
					rb_ary_push(result, e);
					break;
			}
		}
	}

	return result;
}

// The initialization method for this module
void Init_flatten() {
	rb_define_method(rb_cArray, "collapse", method_flatten, -2);
}
