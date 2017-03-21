#include "renderer.h"

int			stack_push(t_obj_stack *stack, t_obj *obj)
{
	if (stack->size >= MAX_REC_DEPTH)
		return (0);
	stack->obj[stack->size] = obj;
	stack->size++;
	return (1);
}

t_obj		*stack_pop(t_obj_stack *stack)
{
	t_obj	*res;
	int		size;

	size = stack->size;
	if (size == 0)
		return (NULL);
	stack->size = stack->size - 1;
	--size;
	res = stack->obj[size];
	stack->obj[size] = NULL;
	return (res);
}

t_obj		*stack_peak(t_obj_stack *stack)
{
	int		size;

	size = stack->size;
	if (size == 0)
		return (NULL);
	return (stack->obj[size - 1]);
}

t_obj_stack		stack_new(void)
{
	int			i;

	t_obj_stack	stack;
	stack.size = 0;
	i = 0;
	while (i < MAX_REC_DEPTH)
		stack.obj[i++] = NULL;
	return (stack);
}
