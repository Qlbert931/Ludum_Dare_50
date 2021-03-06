#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Node.hpp"
#include "Toolkit.hpp"

void Node::updateTransform()
{
    if (parent != NULL)
        updateTransform(parent->getGlobalTransform());
    else
        updateTransform(sf::Transformable());
}

void Node::updateTransform(sf::Transformable const &parent_transform)
{
    m_global_transform = combineTransforms(parent_transform, m_local_transform);

    onTransform();

    for (auto &child : m_children)
    {
        child->updateTransform();
    }
}

void Node::draw(sf::RenderTarget &target)
{
    //std::cout <<"draw " << getName() << std::endl;

    if (!visible)
        return;
    // let the node draw itself
    onDraw(target);

    if(debug_visible) 
        onDrawDebug(target);

    for(auto &child : m_children)
    {
        child ->draw(target);
    }

}

void Node::update(const sf::Time& delta)
{
    //std::cout <<"update " << getName() << std::endl;
    if (!active)
        return;
    onUpdate(delta);

    for(auto &child : m_children)
        child->update(delta);
}

void Node::resize(Resolution resolution)
{
    onResize(resolution);

    for(auto &child : m_children)
    {
        child ->resize(resolution);
    }
}

void Node::addChild(std::shared_ptr<Node> child)
{
    m_children.push_back(child);
    child->parent = this;
    child->setActive(active);
    child->setVisible(visible);
    child->updateTransform();
}

void Node::removeChild(std::shared_ptr<Node> child)
{
    auto element = std::find(m_children.begin(), m_children.end(), child);
    m_children.erase(element);
}

bool Node::isChild(std::shared_ptr<Node> child)
{
    return std::find(m_children.begin(), m_children.end(), child) != m_children.end();
}

void Node::printTree(int depth)
{   
    std::cout << std::string(depth * 4, ' ') << "-" << getName() << "(" << isActive() << ")\n";
    for(auto &child : m_children)
    {
        child -> printTree(depth+1);
    }
    
}

void Node::translate(sf::Vector2f vec)
{
    m_local_transform.move(vec);
    updateTransform();
}

void Node::setTranslation(sf::Vector2f vec)
{
    m_local_transform.setPosition(vec);
    updateTransform();
}

void Node::rotate(float deegres)
{
    m_local_transform.rotate(deegres);
    updateTransform();
}

void Node::setRotation(float deegres)
{
    m_local_transform.setRotation(deegres);
    updateTransform();
}

void Node::scale(sf::Vector2f vec)
{
    m_local_transform.scale(vec);
    updateTransform();
}

void Node::setScale(sf::Vector2f vec)
{
    m_local_transform.setScale(vec);
    updateTransform();
}

sf::Transformable Node::getGlobalTransform() const
{
    return m_global_transform;
}

void Node::printDebug() const {
    std::cout << "==========\n";
    std::cout << "Debug for " << name << ":\n";

    std::cout << "Rel pos: " << m_local_transform.getPosition() << "\n"; 
    std::cout << "Rel rot: " << m_local_transform.getRotation() << "\n"; 
    std::cout << "Rel scale: " << m_local_transform.getScale() << "\n"; 

    std::cout << "Global pos: " << m_global_transform.getPosition() << "\n"; 
    std::cout << "Global rot: " << m_global_transform.getRotation() << "\n"; 
    std::cout << "Global scale: " << m_global_transform.getScale() << "\n"; 
    std::cout << "\n";
}

void Node::onDrawDebug(sf::RenderTarget &target) const
{
    sf::CircleShape point = sf::CircleShape(3.0);
    point.setFillColor(sf::Color(150,50,50,100));
    target.draw(point, getGlobalTransform().getTransform());
}

void Node::setActive(bool _active)
{
    active = _active;
    for (auto& child : m_children)
    {
        child->setActive(_active);
    }
}

void Node::setVisible(bool _visible)
{
    visible = _visible;
    for (auto& child : m_children)
    {
        child->setVisible(visible);
    }
}

bool Node::isActive()
{
    return active;
}
bool Node::isVisible()
{
    return visible;
}
