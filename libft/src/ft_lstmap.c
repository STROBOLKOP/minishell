/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:06:44 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:59 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*iter;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	iter = res;
	lst = lst->next;
	while (lst)
	{
		iter->next = ft_lstnew(f(lst->content));
		if (!iter->next)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		iter = iter->next;
		lst = lst->next;
	}
	return (res);
}

//#include <stdio.h>
//#include <string.h>
//
//void	del_node(void *content)
//{
//	//ft_bzero(content, ft_strlen((char *)content));
//	//ft_strlen((char *)content);
//	free(content);
//	return ;
//}
//
//void	*ft_map_strlen(void *content)
//{
//	size_t	*len;
//	char	*str;
//
//	len = ft_calloc(1, sizeof(size_t));
//	str = (char *)content;
//	while (str[*len])
//		(*len)++;
//	return ((void *)len);
//}
//
//int	main(void)
//{
//	t_list	*list = NULL;
//	ft_lstadd_back(&list, ft_lstnew(ft_strdup("first")));
//	ft_lstadd_back(&list, ft_lstnew(ft_strdup("second")));
//	ft_lstadd_back(&list, ft_lstnew(ft_strdup("third hello")));
//	ft_lstadd_back(&list, ft_lstnew(ft_strdup("fo")));
//	ft_lstadd_back(&list, ft_lstnew(ft_strdup("f")));
//
////	t_list	*list = NULL;
////	ft_lstadd_front(&list, ft_lstnew("FIRST"));
////	ft_lstadd_front(&list, ft_lstnew("SEC"));
////	ft_lstadd_front(&list, ft_lstnew("3"));
////	ft_lstadd_front(&list, ft_lstnew("HELPMEPLEASE"));
//
//	t_list	*head = list;
//
//	while (list)
//	{
//		printf("%s", (char *)list->content);
//		list = list->next;
//		if (list)
//			printf(" -> ");
//	}
//	printf("\nMAP TO STRLEN\n");
//	t_list	*mapped = ft_lstmap(head, ft_map_strlen, del_node);
//	list = mapped;
//	while (list)
//	{
//		printf("%d", *(int *)list->content);
//		list = list->next;
//		if (list)
//			printf(" -> ");
//	}
//
//	ft_lstclear(&mapped, del_node);
//	ft_lstclear(&head, del_node);
//	printf("\n");
//	return (0);
//}
