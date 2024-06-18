/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:47:20 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:56 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}

//#include <stdio.h>
//#include <string.h>
//int	main(void)
//{
//	t_list	*head = NULL;
//	ft_lstadd_front(&head, ft_lstnew(strdup("first")));
//	ft_lstadd_front(&head, ft_lstnew(strdup("second")));
//	ft_lstadd_front(&head, ft_lstnew(strdup("third")));
//	ft_lstadd_front(&head, ft_lstnew(strdup("forth")));
//	ft_lstadd_front(&head, ft_lstnew(strdup("fifth")));
//	while (head)
//	{
//		printf("%s", (char *)head->content);
//		head = head->next;
//		if (head)
//			printf(" -> ");
//	}
//	return (0);
//}
