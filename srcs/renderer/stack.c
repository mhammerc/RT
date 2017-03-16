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
	res = stack->obj[size - 1];
	stack->obj[size - 1] = NULL;
	stack->size--;
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
