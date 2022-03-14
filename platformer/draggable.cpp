void sDrag()
{
    if (left)
    {
        auto e = closestDraggableEntityToMouseClick();
        auto & d = e->getComponent<CDraggable>().dragging;
        if (d) { d = false; }
        else if (mouse click is inside e anim) { d = true; }
    }
}

void sDragAndDrop()
{
    for (auto e : entities)
    {
        if (e->hasComponent<CDraggable>() && 
                e->getComponent<CDraggable>.dragging)
        {
            // set e position to the current mouse pos
        }
    }
}
