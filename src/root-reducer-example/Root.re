open RootReducer;

/* Helpers */
let printItemStatus = itemStatus =>
  switch (itemStatus) {
  | Done(date) => {j|Erledigt am: $date|j}
  | Open => {j|Offen|j}
  };

/* component */
[@react.component]
let make = _ => {
  let (state, dispatch) = React.useReducer(rootReducer, initialState);

  Js.log(state.modalVisible);
  <div
    className="container" style={ReactDOMRe.Style.make(~height="100vh", ())}>
    <RootHeader />
    <div className="row">
      <div className="col">
        <TodoInput
          value={state.newItem.itemName}
          onChange={event =>
            dispatch(UpdateNewItem(event->ReactEvent.Form.target##value))
          }
        />
        <TodoButton
          iconName="plus"
          label="Add"
          onClick={_e => {
            Js.log("AddNewItem Clicked") |> ignore;
            dispatch(AddNewItem);
          }}
        />
      </div>
    </div>
    <table
      className="table table-light table-striped table-bordered table-hover">
      <thead className="thead-dark">
        <tr>
          <th> {React.string("Item")} </th>
          <th> {React.string("Status")} </th>
          <th> {React.string("Actions")} </th>
        </tr>
      </thead>
    
      <tbody>
        {Array.of_list(state.todolist)
         |> Array.map(item =>
              ReasonReact.cloneElement(
                <tr
                  onClick={_e => {
                    Js.log("huhu");
                    dispatch(OpenModal(item));
                  }}
                  key={string_of_int(item.id)}
                />,
                ~props={
                  "data-toggle": "modal",
                  "data-target": "#exampleModal",
                },
                [|
                  <td> {React.string(item.itemName)} </td>,
                  <td>
                    {item.itemStatus |> printItemStatus |> React.string}
                  </td>,
                  <td>
                    <TodoButton
                      iconName="check-square"
                      className="btn btn-success mr-4"
                      label="Check"
                      onClick={_e => dispatch(CloseItem(item.id))}
                    />
                    <TodoButton
                      iconName="trash"
                      className="btn btn-danger"
                      label="Delete"
                      onClick={_e => dispatch(DeleteItem(item.id))}
                    />
                  </td>,
                |],
              )
            )
         |> React.array}
      </tbody>
    </table>
    <Modal visible={state.modalVisible} />
  </div>;
};
