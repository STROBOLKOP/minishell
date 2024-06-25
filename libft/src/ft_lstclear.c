/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:32:17 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:57 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;

	if (*lst == NULL)
		return ;
	iter = (*lst);
	while (iter)
	{
		iter = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = iter;
	}
}

//#include <stdio.h>
//#include <string.h>
//
//void	del_node(void *content)
//{
//	ft_bzero(content, ft_strlen(content));
//}
//
//int	main(void)
//{
//	t_list	*list = NULL;
//	ft_lstadd_back(&list, ft_lstnew(strdup("first")));
//	ft_lstadd_back(&list, ft_lstnew(strdup("second")));
//	ft_lstadd_back(&list, ft_lstnew(strdup("third")));
//	ft_lstadd_back(&list, ft_lstnew(strdup("forth")));
//	ft_lstadd_back(&list, ft_lstnew(strdup("fifth")));
//	t_list	*head = list;
//	while (list)
//	{
//		printf("%s", (char *)list->content);
//		list = list->next;
//		if (list)
//			printf(" -> ");
//	}
//	ft_lstclear(&(head->next->next), del_node);
//	printf("\nDELETED\n");
//	list = head;
//	while (list)
//	{
//		printf("%s", (char *)list->content);
//		list = list->next;
//		if (list)
//			printf(" -> ");
//	}
//	return (0);
//}
