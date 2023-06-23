/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 07:35:43 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 19:17:23 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <vector>

/**
 * The function prints out information about a given Message object.
 * 
 * @param command The parameter "command" is a constant reference to an object
 * of the class "Message".
 */
void	debug::print_message(const Message& command)
{
	std::cout << "prefix: " << command.getPrefix() << std::endl;
	std::cout << "params:" << std::endl;
	for (std::vector<std::string>::const_iterator it = command.getParams().begin(); it != command.getParams().end(); it++)
		std::cout << "	[" << *it << "]" << std::endl;
	std::cout << "trailing: " << command.getTrailing() << std::endl;
	std::cout << "has trailing: " << command.getHasTrailing() << std::endl;
	std::cout << std::endl;
}
