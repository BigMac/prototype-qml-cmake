#ifndef QTSERVICEFSMGUARDS_H
#define QTSERVICEFSMGUARDS_H

// Guards
template<typename Guard>
struct Not : private Guard
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    bool operator()(Evt const& evt, Fsm& fsm, SourceState& ss ,TargetState& ts)
    {
        return ! Guard::operator()(evt, fsm, ss, ts);
    }
};

struct DrawBufferResponseOk
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    bool operator()(Evt const& evt, Fsm& fsm, SourceState&,TargetState& )
    {
        //fsm->submit(DrawBufferRequest);
        return true; // TEMP
    }
};

struct GuiResourceResponseOk
{
    template <class Fsm,class Evt,class SourceState,class TargetState>
    bool operator()(Evt const& evt, Fsm&, SourceState& ss, TargetState& )
    {
        return ss.requestedUrl == evt.getUrl();
    }
};

#endif // QTSERVICEFSMGUARDS_H
