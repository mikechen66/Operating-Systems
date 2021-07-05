
/ * Figure 2-34. 
  * An outline of the producer-consumer problem with monitors. Only one  
  * monitor procedure at a time is active. The buffer has N slots.
  */


monitor ProducerConsumer 
    condition full, empty;
    integer count;

    procedure insert(item: integer); 
    begin
        if count = N then wait(full); 
        insert_item(item);
        count := count + 1;
        if count = 1 then signal(empty)
    end;

    function remove: integer; 
    begin
        if count = 0 then wait(empty); 
        remove = remove_item;
        count := count − 1;
        if count = N − 1 then signal(full)
    end; 

    count := 0;
end monitor;


procedure producer; 
begin
    while true do 
    begin
        item = producer_item; 
        ProducerConsumer.insert(item)
    end 
end;


procedure consumer; 
begin
    while true do 
    begin
        item = ProducerConsumer.remove;
        consumer_item(item)
    end
end;
