/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:57:36 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:56 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*iter;

	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	iter = *lst;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
}

//#include <stdio.h>
//#include <string.h>
//int	main(void)
//{
//	t_list	*head = NULL;
//	ft_lstadd_back(&head, ft_lstnew(strdup("first")));
//	ft_lstadd_back(&head, ft_lstnew(strdup("second")));
//	ft_lstadd_back(&head, ft_lstnew(strdup("third")));
//	ft_lstadd_back(&head, ft_lstnew(strdup("forth")));
//	ft_lstadd_back(&head, ft_lstnew(strdup("fifth")));
//	while (head)
//	{
//		printf("%s", (char *)head->content);
//		head = head->next;
//		if (head)
//			printf(" -> ");
//	}
//	return (0);
//}
