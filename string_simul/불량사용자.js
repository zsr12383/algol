let banSiz, userSiz;
let visit=[];
let answer = 0;
let userId;
let bannedId;

function dfs(level, mask)
{
    if(level === banSiz){
        if(!visit[mask]){
            console.log(mask);
            visit[mask] = true;
            answer++;
        }
        return;
    }
    for(let i = 0 ; i < userSiz; i++){
        if(mask & (1 << i)) continue;
        const res = userId[i].match(bannedId[level]);
        if(!res) continue;
        dfs(level + 1, mask | (1 << i));
    }
        
}

function solution(user_id, banned_id) {
    userId = user_id;
    bannedId = banned_id.map(ele => ele.replace(/\*/g, '.')).map(ele => new RegExp(`^${ele}\$`));
    banSiz = banned_id.length;
    userSiz = userId.length;
    dfs(0, 0);
    return answer;
}